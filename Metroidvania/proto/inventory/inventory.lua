 -- outer edges without titlebar
local target_width = 298
local target_height = 192

-- font for texts
local font_file = app.load_font("Sevenet7Cyr.ttf")
local font_size = 8

local footer_text = "x - действие, b - выбросить, z - в слот, s - другой слот"

local total_slots = 5
local pages =
{
    { title = " статус " },
    { title = " заклинания " },
    { title = " вещи " },
    { title = " меню " }
}

local current_page = 3
local current_slot = 1
local current_item_row = 6


local menu_x, menu_y = 64, 50

-- tab text colors
local active_tab_color = {0,0,0,255}
local inactive_tab_color = {255,229,213,255}

-- item list colors
local item_color =
{
    epic = {255,227,108,255},
    consumable = {92,251,66,255},
    normal = {255,255,255,255}
}

----------------------------------------
-- make local copies of global functions for speedup
local load_image = app.load_image
local load_file = app.load_file
local new_program = app.new_program
local use_program = app.use_program
local new_texture = app.new_texture
local sprite_set = app.sprite_set
local bind_texture = app.bind_texture
local texture_filter = app.texture_filter
local vao, vbo = app.vao, app.vbo
local blend, blend_func = app.blend,app.blend_func
local vertex_shader = app.vertex_shader
local fragment_shader = app.fragment_shader
local ipairs, pairs = ipairs, pairs


-- menu size after adjustments
local actual_width, actual_height
local estimated_items_width, estimated_items_height

local backpack_items, current_item
local visible_items, total_items, list_text_y, list_layout
local top_visible_item, bottom_visible_item, item_row_height

local slots = {}

-- load known items
local known_items = {}

loadfile("items.lua", "bt",
    setmetatable(
    {
        epic = "epic",
        consumable = "consumable"
    },{
        -- report invalid properties
        __index = function(t,k) print("Illegal property '"..k.."'") end,
        -- collect items
        __newindex = function(_,k,v) known_items[k] = v end
    })
)()

-- load items' images
for k,v in pairs(known_items) do
    local name = "items/" .. v.icon
    v.img = load_image(name)
end

local inventory_decor =
{
    bg = "bg.png",
    corner = "corner.png",
    expand = "expand.png",
    game = "game.png",
    icon_bg = "icon_bg.png",
    item_select = "item_select.png",
    rect = "rect.png",
    scroller_bg = "scroller_bg.png",
    scroller_fill = "scroller_fill.png",
    scroller_up = "scroller_up.png",
    slot = "slot.png",
    slot_select = "slot_select.png",
    tab_left = "tab_left.png",
    tab_select = "tab_select.png",
    titlebar = "titlebar.png",
    top_left = "top_left.png"
}

local inventory_set, decor_texture

local inventory_path = "inventory/"
local frag_source = load_file(inventory_path.."inventory.frag")
local vert_source = load_file(inventory_path.."inventory.vert")

for name,file in pairs(inventory_decor) do
    inventory_decor[name] = { img = load_image(inventory_path..file) }
end

local function vec2f(array)
    array.type = "float"
    array.size = 2
    return array
end

local function vec4b(array)
    array.type = "char"
    array.size = 4
    return array
end

local function update_vao(buffer, pos, uv, color, index)

    -- reuse existing buffers or create new
    local existing_vao = buffer.vao or vao()

    local verts = existing_vao.verts or vbo()

    verts.pos = vec2f(pos)
    verts.uv = vec2f(uv)
    verts.color = vec4b(color)

    local indices = existing_vao.index or vbo()
    indices.index = index

    existing_vao.verts = verts
    existing_vao.index = indices

--[[
    -- dumb create without reusing
    existing_vao = vao {
        vbo { pos = vec2f(pos), uv = vec2f(uv), color = vec4b(color)},
        vbo { index = index }
    }
--]]

    buffer.vao = existing_vao
    buffer.ok = true
end

local shader
local static_text_set, static_text_texture
local items_set, list_set
local font, descender, ascender
local titlebar_height
local footer_sprite_idx, footer_width
local description_set, description_layout, description_texture
local quantity_tex
local textures_ok, item_changed, update_quantity
local bg_buffer, static_text_buffer, icons_buffer, items_list_buffer, cursor_buffer = {},{},{},{},{}
local description_buffer, quantity_buffer = {}, {}

local slot_size, slots_range
local slots_gap = 14

local idx_pattern = {0,1,2,2,3,0}

local function simple_buffer_scaled()
    local verts, texco, indices = {}, {}, {}

    local verts_size = 0
    local indices_size = 0
    local total_verts = 0

    -- append sprite to buffers
    local function append(sprite, x, y, scale_x, scale_y)

        local invert_x, invert_y

        if scale_x<0 then
            scale_x = -scale_x
            invert_x = true
        end
        if scale_y<0 then
            scale_y = -scale_y
            invert_y = true
        end

        local pos = sprite.verts
        local uv = sprite.texco

        for i=1,8,2 do
            local ni = i+1
            -- scale and translate sprite
            verts[verts_size+i] = pos[i]*scale_x + x
            verts[verts_size+ni] = pos[ni]*scale_y + y

            -- texture coordinates copied as-is
            texco[verts_size+i] = uv[i]
            texco[verts_size+ni] = uv[ni]
        end

        -- sprite's quad is built like this:
        --
        --  3 ------2
        --          |
        --          |
        --          |
        --  0 ------1

        if invert_x then
            -- swap texture coords
            texco[verts_size+1], texco[verts_size+3] = texco[verts_size+3], texco[verts_size+1]
            texco[verts_size+5], texco[verts_size+7] = texco[verts_size+7], texco[verts_size+5]
        end

        if invert_y then
            -- swap texture coords
            texco[verts_size+2], texco[verts_size+8] = texco[verts_size+8], texco[verts_size+2]
            texco[verts_size+4], texco[verts_size+6] = texco[verts_size+6], texco[verts_size+4]
        end

        -- append indices for new quad
        for i=1,6 do
            indices[indices_size+i] = idx_pattern[i] + total_verts
        end

        verts_size = verts_size + 8 -- 2*4 coords
        indices_size = indices_size + 6
        total_verts = total_verts + 4
    end

    local function buffers()
        local color ={}
        for i=1,4*total_verts do
            color[i] = 255
        end
        return verts, texco, color, indices
    end

    return append, buffers
end

local function sprite(name)
    return inventory_set:get_sprite(inventory_decor[name].idx)
end

local function new_static_bg()
    local append, buffers = simple_buffer_scaled()

    -- window's outer decoration coords
    local corner_size = inventory_decor.corner.size
    local top_left_size = inventory_decor.top_left.size
    local expand_size = inventory_decor.expand.size

    local left_near_x = corner_size[1]
    local top_x = left_near_x + top_left_size[1]
    local right_near_x = math.max(top_x, target_width - top_x)
    local right_corner_x = right_near_x + top_left_size[1]

    actual_width = right_corner_x + corner_size[1]

    local side_y = -corner_size[2]
    local right_x = actual_width - expand_size[1]
    local left_bottom_corner_y = corner_size[2]-target_height

    local bottom_x = corner_size[1]
    local bottom_y = expand_size[2] - target_height
    local right_bottom_corner_x =  actual_width - corner_size[1]

    actual_height = target_height

    local expand_sprite = sprite("expand")
    local corner_sprite = sprite("corner")
    local top_left_sprite = sprite("top_left")

    -- game mockup first
    append(sprite("game"), -menu_x/2, menu_y/2, 1, 1)

    -- transparent menu bg
    local bg_size = inventory_decor.bg.size
    append(sprite("bg"),
            expand_size[1], -expand_size[2],
            (actual_width-2*expand_size[1])/bg_size[1],
            (actual_height-2*expand_size[2])/bg_size[2])

    -- now corners
    append(corner_sprite, 0,0, 1,1)
    append(top_left_sprite, left_near_x, 0, 1,1)
    append(top_left_sprite, right_near_x, 0, -1,1)
    append(corner_sprite, right_corner_x, 0, -1,1)
    append(corner_sprite, 0, left_bottom_corner_y, 1,-1)
    append(corner_sprite, right_bottom_corner_x, left_bottom_corner_y, -1,-1)

    --  and expandable borders
    local side_height = (target_height-2*corner_size[2])/expand_size[2]
    -- left/right
    append(expand_sprite, 0, -corner_size[2], 1, side_height)
    append(expand_sprite, actual_width-expand_size[1], -corner_size[2], 1, side_height)
    -- top/bottom
    append(expand_sprite, top_x, 0, (right_near_x - top_x)/expand_size[1], 1)
    append(expand_sprite, bottom_x, bottom_y, (actual_width-2*corner_size[1])/expand_size[1], 1)


    -- titlebar
    local tab_left_size = inventory_decor.tab_left.size
    local tab_left_sprite = sprite("tab_left")
    local titlebar_size = inventory_decor.titlebar.size
    local titlebar_x = 4+tab_left_size[1]

    titlebar_height = titlebar_size[2]

    -- estimate tabs names width
    local sum_pages_width = 0
    for i,page in ipairs(pages) do
        local width = font:estimate(page.title)
        page.title_width = width
        page.title_x = titlebar_x + sum_pages_width
        sum_pages_width = sum_pages_width+width
    end

    -- arrows and titlebar bg
    append(tab_left_sprite, 4, tab_left_size[2], 1,1)
    append(sprite("titlebar"), titlebar_x, titlebar_height, sum_pages_width/titlebar_size[1], 1)
    append(tab_left_sprite, titlebar_x+sum_pages_width, tab_left_size[2], -1, 1)

    -- tab selection bar
    local tab_select_size = inventory_decor.tab_select.size
    local page = pages[current_page]
    append(sprite("tab_select"), page.title_x, titlebar_size[2]-1, page.title_width/tab_select_size[1], 1)


    -- slots
    local slot_size = inventory_decor.slot.size
    slots_range = slots_gap+slot_size[1]

    local slots_x, slots_y = 15,-15
    local slot_sprite = sprite("slot")

    for i=1,total_slots do
        local x = (i-1)*slots_range + slots_x
        if i~=current_slot then
            append(slot_sprite, x, slots_y, 1, 1)
        else
            append(sprite("slot_select"), x, slots_y+1, 1, 1)
        end
    end

    -- items list and scroller borders
    local rect_size = inventory_decor.rect.size
    local scroller_bg_size = inventory_decor.scroller_bg.size

    local rect_sprite = sprite("rect")
    local rect_x, rect_y = 15, -63
    list_content_y = rect_y-1

    estimated_items_width = 121
    estimated_items_height = 112 +4 -- +4 to better fit +1 pixel distance between items
    local rect_x_scale = (estimated_items_width+scroller_bg_size[1])/rect_size[1]+3
    local rect_y_scale = estimated_items_height/rect_size[2]
    append(rect_sprite, rect_x, rect_y, rect_x_scale, 1)
    append(rect_sprite, rect_x, rect_y-rect_size[2], 1, rect_y_scale)
    append(rect_sprite, rect_x + rect_size[1]+estimated_items_width, rect_y-rect_size[2], 1, rect_y_scale)
    append(rect_sprite, rect_x + rect_size[1]+estimated_items_width+rect_size[1]+scroller_bg_size[1], rect_y-rect_size[2], 1, rect_y_scale)
    append(rect_sprite, rect_x, rect_y-rect_size[2]-estimated_items_height, rect_x_scale, 1)

    -- current item's bg
    local icon_bg_size = inventory_decor.icon_bg.size
    local width, height = 122, 32
    append(sprite("icon_bg"), 160, -64, width/icon_bg_size[1], height/icon_bg_size[2])

    update_vao(bg_buffer, buffers())
end

-- simple sprite buffering with offset and color
local function simple_buffer_color()
    local verts, texco, indices = {}, {}, {}
    local colors = {}

    local pos_count = 0
    local total_verts = 0
    local indices_size = 0
    local colors_size = 0

    local function append(sprite, x, y, color)
        local pos = sprite.verts
        local uv = sprite.texco

        for i=1,8,2 do
            verts[pos_count+i]   = pos[i] + x
            verts[pos_count+i+1] = pos[i+1] + y
        end

        for i=1,8 do
            texco[pos_count+i] = uv[i]
        end

        for i=1,6 do
            indices[indices_size+i] = idx_pattern[i] + total_verts
        end

        for i=1,16,4 do
            local idx = colors_size+i
            colors[idx] = color[1]
            colors[idx+1] = color[2]
            colors[idx+2] = color[3]
            colors[idx+3] = color[4]
        end

        pos_count = pos_count + 8
        total_verts = total_verts + 4
        indices_size = indices_size + 6
        colors_size = colors_size + 16
    end

    local function buffers()
        return verts, texco, colors, indices
    end

    return append, buffers
end

-- simple sprite buffering with offset only
local function simple_buffer()
    local verts, texco, indices = {}, {}, {}

    local pos_count = 0
    local total_verts = 0
    local indices_size = 0

    local function append(sprite, x, y)
        local pos = sprite.verts
        local uv = sprite.texco

        for i=1,8,2 do
            verts[pos_count+i]   = pos[i] + x
            verts[pos_count+i+1] = pos[i+1] + y
        end

        for i=1,8 do
            texco[pos_count+i] = uv[i]
        end

        for i=1,6 do
            indices[indices_size+i] = idx_pattern[i] + total_verts
        end

        pos_count = pos_count + 8
        total_verts = total_verts + 4
        indices_size = indices_size + 6
    end

    local function buffers()
        local color ={}
        for i=1,4*total_verts do
            color[i] = 255
        end
        return verts, texco, color, indices
    end

    return append, buffers
end


-- pack menu static texts buffer
local function new_static_text()
    local append, buffers = simple_buffer_color()

    local height = ascender-descender

    local pos_y = math.floor((titlebar_height-height)/2-descender)

    for i,page in ipairs(pages) do
        append(static_text_set:get_sprite(page.title_sprite_idx), page.title_x, pos_y, i~=current_page and inactive_tab_color or active_tab_color)
    end

    local footer_sprite = static_text_set:get_sprite(footer_sprite_idx)
    append(footer_sprite, math.floor((actual_width-footer_width)*0.5), -actual_height-ascender-1, {219,195,110,255})

    update_vao(static_text_buffer, buffers())
end


-- pack item icons buffer
local function new_icons_buf()
    local append, buffers = simple_buffer()

    local slots_x, slots_y = 16+16,-16-16

    for i=1,total_slots do
        local item = slots[i]
        if item then
            append(items_set:get_sprite(item.sprite_idx), slots_x+(i-1)*slots_range, slots_y)
        end
    end

    if current_item then
        append(items_set:get_sprite(current_item.sprite_idx), 222, -80)
    end

    update_vao(icons_buffer, buffers())
end

-- pack current item description buffer
local function new_item_description()
    local append, buffers = simple_buffer()

    local text_x, text_y = 164 , -103
    local text_width_limit = 114

    description_set = sprite_set()
    description_layout = {}
    description_buffer.shown = false

    if current_item then
        local description = current_item.description
        if description then
            local text_pos = 0
            local row_i = 1
            local inserted

            -- estimate text layout
            repeat
                local width, next_word, cache = font:estimate(description, text_pos, text_width_limit)

                if width then
                    table.insert(description_layout, {text_pos, cache, row_i})
                    inserted = true
                    row_i = row_i+1
                else
                    if not inserted then
                        row_i = row_i+1
                    end
                    inserted = false
                end
                text_pos = next_word
            until not next_word

            -- paint words in image
            for _,line in ipairs(description_layout) do
                line.sprite_idx = description_set:add_image( font:draw(description, line[1], text_width_limit) )
            end

            -- build buffer
            local interval = 1
            local height = font:get_height()*interval
            text_y = text_y - ascender

            for _,line in ipairs(description_layout) do
                append(description_set:get_sprite(line.sprite_idx), text_x, text_y - math.floor((line[3]-1)*height))
            end

            local image = description_set:image()
            if description_texture then
                description_texture:update(image)
            else
                description_texture = new_texture(image)
            end
            texture_filter("mag","nearest")

            update_vao(description_buffer, buffers())
            description_buffer.shown = true
        end
    end
end

-- pack items list buffer
local function new_item_list()
    local append, buffers = simple_buffer_color()

    local list_x, list_y = 21, list_content_y-ascender
    local normal = item_color.normal

    local interval = 1
    item_row_height = font:get_height()*interval +1

    visible_items = math.floor((estimated_items_height)/item_row_height)
    list_y = list_y - math.floor((estimated_items_height - visible_items*item_row_height)/2)
    list_text_y = list_y

    for i, slot in ipairs(backpack_items) do
        local item = slot[1]
        local color = item_color[item[1]] or normal
        append(list_set:get_sprite(item.sprite_idx), list_x, math.floor(-(i-1)*item_row_height)+list_y, color)
    end

    update_vao(items_list_buffer, buffers())
end

local function new_cursor()
    cursor_buffer.shown = false

    if current_item then
        local append, buffers = simple_buffer_scaled()

        local window = math.min(total_items, visible_items)
        local window_top = math.max(1, current_item_row - math.floor(visible_items/2))
        local window_bottom = math.min(total_items, window_top + window-1)
        window_top = window_bottom - window+1

        top_visible_item = window_top
        bottom_visible_item = window_bottom

        local cursor_size = inventory_decor.item_select.size

        -- item's cursor
        append(sprite("item_select"),
                16, list_text_y + ascender + 1 - (current_item_row - window_top)*item_row_height,
                estimated_items_width/cursor_size[1],
                (ascender-descender+2)/cursor_size[2])

        -- scroller
        local scroller_height = estimated_items_height
        local scroller_up = inventory_decor.scroller_up.size

        local slider_height = math.max(scroller_up[2]*2, math.floor(window*scroller_height/total_items))
        local slider_fill = slider_height - scroller_up[2]*2

        local empty_height = scroller_height-slider_height
        local rows_higher = window_top-1
        local empty_top = 0
        if total_items>window then
            empty_top = math.floor(empty_height*rows_higher/(total_items-window))
        end
        local empty_bottom = empty_height - empty_top

        local up_sprite = sprite("scroller_up")
        local scroller_bg = sprite("scroller_bg")
        local scroller_up_size = inventory_decor.scroller_up.size
        local scroller_bg_size = inventory_decor.scroller_bg.size

        local x = 16 + estimated_items_width+inventory_decor.rect.size[1]
        local y = list_content_y
        append(scroller_bg, x, y, 1, empty_top/scroller_bg_size[2])
        y = y - empty_top
        append(up_sprite, x, y, 1, 1)
        y = y - scroller_up_size[2]
        append(sprite("scroller_fill"), x, y, 1, slider_fill/inventory_decor.scroller_fill.size[2])
        y = y - slider_fill
        append(up_sprite, x, y, 1, -1)
        y = y - scroller_up_size[2]
        append(scroller_bg, x, y, 1, empty_bottom/scroller_bg_size[2])

        update_vao(cursor_buffer, buffers())
        cursor_buffer.shown = true
    end
end

local function new_quantities()
    -- collect rows with >1 items
    local rows = {}

    for i=top_visible_item, bottom_visible_item do
        local backpack_slot = backpack_items[i]
        if backpack_slot then
            local quant = backpack_slot[2]
            if quant>1 then
                table.insert(rows, {i, quant})
            end
        end
    end

    quantity_buffer.shown = false
    quantity_set = sprite_set()

    if #rows>0 then
        local normal = item_color.normal
        for i,row in ipairs(rows) do
            local text = " ("..row[2]..")"
            row.sprite = quantity_set:add_image(font:draw(text))
        end

        local append, buffers = simple_buffer_color()

        for i,row in ipairs(rows) do
            local slot_idx = row[1]
            local item = backpack_items[slot_idx][1]
            local color = item_color[item[1]] or normal
            local x = 21+list_layout[slot_idx][1]
            local y = list_text_y-(slot_idx-top_visible_item)*item_row_height
            append(quantity_set:get_sprite(row.sprite), x, y, color)
        end

        update_vao(quantity_buffer, buffers())
        quantity_buffer.shown = true

        local image = quantity_set:image()
        if quantity_tex then
            quantity_tex:update(image)
        else
            quantity_tex = new_texture(image)
        end
        texture_filter("mag","nearest")
    end
end

-- called when all external files loaded and before any drawing
local function build()

    font = font_file:get_face(font_size)
    font:adjust_spacing(1)

    ascender = font:get_ascender()
    descender = font:get_descender()

    items_set = sprite_set()

    for _,item in pairs(known_items) do
        local img = item.img
        local width, height = img:size()
        item.sprite_idx = items_set:add_image(img, width/2, height/2)
    end

    inventory_set = sprite_set()
    for k,v in pairs(inventory_decor) do
        v.size = {v.img:size()}
        v.idx = inventory_set:add_image(v.img)
    end

    -- generate backpack content
    -- right now just insert all known items
    backpack_items = {}

    -- later we'll need item->idx dictionary, but not now
    for _,item in pairs(known_items) do
        local quantity = 1
        if item[1] == "consumable" then
            quantity = math.random(20)
        end
        table.insert(backpack_items, {item, quantity})
    end
    total_items = #backpack_items

    -- fake initial slots
    slots[1] = known_items.grass
    slots[2] = known_items.hamburger
    slots[3] = known_items.fairy
    slots[4] = known_items.axe
    slots[5] = known_items.knife
end

local function restored()
    -- signal gpu was lost
    textures_ok = false

    bg_buffer = {}
    static_text_buffer={}
    icons_buffer={}
    items_list_buffer={}
    cursor_buffer={}
    description_buffer = {}
    quantity_buffer = {}
end

local scale = 2

local screen_width, screen_height

local scaling_matrix =
{
    1, 0, 0,
    0, 1, 0,
    0, 0, 1
}

local function transform(x, y)
    scaling_matrix[3] = x/(screen_width*0.5)-1
    scaling_matrix[6] = -y/(screen_height*0.5)+1
    return scaling_matrix
end

local function upload_textures()
    -- recreate gpu resources
    static_text_set = sprite_set()

    -- fill image with static texts
    for i,page in ipairs(pages) do
        local image,spot_x,spot_y = font:draw(page.title)
        page.title_sprite_idx = static_text_set:add_image(image, spot_x, spot_y)
    end

    footer_width = font:estimate(footer_text)
    footer_sprite_idx = static_text_set:add_image(font:draw(footer_text))

    static_text_texture = new_texture(static_text_set:image())
    texture_filter("mag","nearest")

    list_set = sprite_set()
    list_layout = {}

    for i, slot in ipairs(backpack_items) do
        local name = slot[1].name
        local width, _, cache = font:estimate(name)
        list_layout[i] = {width, cache}
        slot.sprite_idx = list_set:add_image(font:draw(name))
    end

    list_texture = new_texture(list_set:image())
    texture_filter("mag","nearest")

    decor_texture = new_texture(inventory_set:image())
    texture_filter("mag","nearest")

    items_texture = new_texture(items_set:image())
    texture_filter("mag","nearest")

    shader = new_program(vertex_shader(vert_source),fragment_shader(frag_source))
end

local function rebuild_static_background()
    new_static_bg()
    new_static_text()
end

local function draw_all(swidth, sheight)
    screen_width, screen_height = swidth, sheight
    scaling_matrix[1] = 2/swidth*scale
    scaling_matrix[5] = 2/sheight*scale

    if not textures_ok then
        upload_textures()
        textures_ok = true
        item_changed = true
    end

    if not bg_buffer.ok then
        rebuild_static_background()
    end

    if not items_list_buffer.ok then
        new_item_list()
    end

    if item_changed then
        item_changed = false
        current_item = nil
        local backpack_slot = backpack_items[current_item_row]
        if backpack_slot then
            current_item = backpack_slot[1]
        end

        new_cursor()
        new_item_description()
        icons_buffer.ok = false
        update_quantity = true
    end

    if update_quantity then
        update_quantity = false
        new_quantities()
    end

    if not icons_buffer.ok then
        new_icons_buf()
    end


    blend "add"
    blend_func("src_alpha", "inv_src_alpha")

    bind_texture(0, decor_texture)
    use_program(shader)

    shader.tex = 0

    -- it seems radeon hd4800 can't or won't support per-instance data for attributes
    -- all data must go in vertex arrays
    -- shader.color = {1,1,1,1}
    shader.mv = transform(menu_x, menu_y)

    bg_buffer.vao:draw "triangles"

    if cursor_buffer.shown then
        cursor_buffer.vao:draw "triangles"
    end

    bind_texture(0, static_text_texture)
    static_text_buffer.vao:draw "triangles"

    bind_texture(0, items_texture)
    icons_buffer.vao:draw "triangles"

    if description_buffer.shown then
        bind_texture(0, description_texture)
        --shader.color = {219/255,195/255,110/255,1} -- not working on amd/ati
        description_buffer.vao:draw "triangles"
    end

    if quantity_buffer.shown then
        bind_texture(0, quantity_tex)
        quantity_buffer.vao:draw "triangles"
    end

    bind_texture(0, list_texture)
    shader.mv = transform(menu_x, menu_y - (top_visible_item-1)*item_row_height*scale)
    items_list_buffer.vao:draw("triangles", (top_visible_item-1)*6, (bottom_visible_item-top_visible_item+1)*6)
end


----------------------------------------------------------
--
--   Keyboard interaction
--
----------------------------------------------------------
local function tab_right()
    current_page = math.fmod(current_page, #pages) + 1
    bg_buffer.ok = false
end

local function tab_left()
    current_page = current_page - 1
    if current_page<1 then
        current_page = #pages
    end
    bg_buffer.ok = nil
end

local function list_up()
    current_item_row = math.max(current_item_row-1, 1)
    item_changed = true
end

local function list_down()
    current_item_row = math.min(current_item_row+1, #backpack_items)
    item_changed = true
end

local function next_slot()
    current_slot = math.fmod(current_slot, total_slots) + 1
    bg_buffer.ok = false
end

local function item_to_slot()
    if current_item and slots[current_slot]~=current_item then
        slots[current_slot] = current_item
        icons_buffer.ok = nil
    end
end

local function item_lost(drop_all)
    if current_item_row>0 then
        local backpack_slot = backpack_items[current_item_row]
        local count = backpack_slot[2]-1
        backpack_slot[2] = count
        if count<1 or drop_all then
            table.remove(list_layout, current_item_row)
            local item = table.remove(backpack_items, current_item_row)[1]

            -- clean slots with lost item
            for i=1,total_slots do
                if slots[i] == item then
                    slots[i] = nil
                end
            end

            current_item_row = math.min(current_item_row, #backpack_items)
            total_items = #backpack_items
            items_list_buffer.ok = false
            item_changed = true
        else
            update_quantity = true
        end
    end
end

local function consume_item()
    if current_item_row>0 and backpack_items[current_item_row][1][1] == "consumable" then
        item_lost()
    end
end

app.queue_suspend()
build()

return {
    draw = draw_all,
    build = build,
    restored = restored,
    tab_left = tab_left,
    tab_right = tab_right,
    list_up = list_up,
    list_down = list_down,
    next_slot = next_slot,
    item_to_slot = item_to_slot,
    drop_item = function() item_lost(true) end,
    use_item = consume_item,
}

