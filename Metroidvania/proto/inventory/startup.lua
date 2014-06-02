math.randomseed(os.time())

local clear = app.clear

local render_enabled, render_active
local swidth, sheight

local inventory = dofile "inventory.lua"

local menu_keys =
{
    [37] = "tab_left",
    [39] = "tab_right",
    [38] = "list_up",
    [40] = "list_down",
    [83] = "next_slot",
    [88] = "use_item",
    [90] = "item_to_slot",
    [66] = "drop_item"
}

return {
    iterate = function(events, current_time)
        for e in events do

            if e.kind == "key" and e.type == "key_press" then
                local key = menu_keys[e.keysym]
                if key then
                    local action = inventory[key]
                    if action then action() end
                end
            end

            if e.kind == "context" then
                -- got rendering context recreated
                if e.type == "restored" then

                    render_enabled = true
                    -- signal menu to recreate gpu resources
                    inventory.restored()

                    -- remember current viewport size
                    swidth,sheight = e.width, e.height
                end
            end
        end

        if render_enabled then
            clear()
            inventory.draw(swidth, sheight)
        end
    end,

    change_state = function(state)
        if state==3 then
            if window_manager and not render_active then
                -- it's desktop environment, must create window ourselves
                local width, height, fullscreen = 720, 480

                window_manager.setup_window(width, height, fullscreen)
            end

            render.create_context(color_depth, depth_resolution, multisample_level)
            render_active = true
        else
            render_enabled = false
        end
    end
}
