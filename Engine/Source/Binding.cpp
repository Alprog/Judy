/*
** Lua binding: Binding
** Generated automatically by tolua++-1.0.92 on 09/08/14 17:29:50.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_Binding_open (lua_State* tolua_S);

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "App.h"
#include "Window.h"
#include "Node.h"
#include "Quad.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_Quad (lua_State* tolua_S)
{
 Quad* self = (Quad*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Node (lua_State* tolua_S)
{
 Node* self = (Node*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_size_t (lua_State* tolua_S)
{
 size_t* self = (size_t*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"App");
 tolua_usertype(tolua_S,"Quad");
 tolua_usertype(tolua_S,"Vector2");
 tolua_usertype(tolua_S,"Renderer");
 tolua_usertype(tolua_S,"Window");
 tolua_usertype(tolua_S,"Node");
 tolua_usertype(tolua_S,"size_t");
}

/* get function: Zero of class  Vector2 */
#ifndef TOLUA_DISABLE_tolua_get_Vector2_Zero
static int tolua_get_Vector2_Zero(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)&Vector2::Zero,"const Vector2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: One of class  Vector2 */
#ifndef TOLUA_DISABLE_tolua_get_Vector2_One
static int tolua_get_Vector2_One(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)&Vector2::One,"const Vector2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: x of class  Vector2 */
#ifndef TOLUA_DISABLE_tolua_get_Vector2_x
static int tolua_get_Vector2_x(lua_State* tolua_S)
{
  Vector2* self = (Vector2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->x);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: x of class  Vector2 */
#ifndef TOLUA_DISABLE_tolua_set_Vector2_x
static int tolua_set_Vector2_x(lua_State* tolua_S)
{
  Vector2* self = (Vector2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->x = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: y of class  Vector2 */
#ifndef TOLUA_DISABLE_tolua_get_Vector2_y
static int tolua_get_Vector2_y(lua_State* tolua_S)
{
  Vector2* self = (Vector2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->y);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: y of class  Vector2 */
#ifndef TOLUA_DISABLE_tolua_set_Vector2_y
static int tolua_set_Vector2_y(lua_State* tolua_S)
{
  Vector2* self = (Vector2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->y = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Length of class  Vector2 */
#ifndef TOLUA_DISABLE_tolua_Binding_Vector2_Length00
static int tolua_Binding_Vector2_Length00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Vector2",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Vector2* self = (Vector2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Length'", NULL);
#endif
  {
   float tolua_ret = (float)  self->Length();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Length'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SquaredLength of class  Vector2 */
#ifndef TOLUA_DISABLE_tolua_Binding_Vector2_SquaredLength00
static int tolua_Binding_Vector2_SquaredLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Vector2",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Vector2* self = (Vector2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SquaredLength'", NULL);
#endif
  {
   float tolua_ret = (float)  self->SquaredLength();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SquaredLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Instance of class  App */
#ifndef TOLUA_DISABLE_tolua_Binding_App_Instance00
static int tolua_Binding_App_Instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"App",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   App* tolua_ret = (App*)  App::Instance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"App");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Instance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: StartMainLoop of class  App */
#ifndef TOLUA_DISABLE_tolua_Binding_App_StartMainLoop00
static int tolua_Binding_App_StartMainLoop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"App",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  App* self = (App*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StartMainLoop'", NULL);
#endif
  {
   self->StartMainLoop();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StartMainLoop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddWindow of class  App */
#ifndef TOLUA_DISABLE_tolua_Binding_App_AddWindow00
static int tolua_Binding_App_AddWindow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"App",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Window",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  App* self = (App*)  tolua_tousertype(tolua_S,1,0);
  Window* window = ((Window*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddWindow'", NULL);
#endif
  {
   self->AddWindow(window);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddWindow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveWindow of class  App */
#ifndef TOLUA_DISABLE_tolua_Binding_App_RemoveWindow00
static int tolua_Binding_App_RemoveWindow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"App",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Window",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  App* self = (App*)  tolua_tousertype(tolua_S,1,0);
  Window* window = ((Window*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveWindow'", NULL);
#endif
  {
   self->RemoveWindow(window);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveWindow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Create of class  Window */
#ifndef TOLUA_DISABLE_tolua_Binding_Window_Create00
static int tolua_Binding_Window_Create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Window",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Window* tolua_ret = (Window*)  Window::Create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Window");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: show of class  Window */
#ifndef TOLUA_DISABLE_tolua_Binding_Window_show00
static int tolua_Binding_Window_show00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Window",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Window* self = (Window*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'show'", NULL);
#endif
  {
   self->show();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'show'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ProcessEvents of class  Window */
#ifndef TOLUA_DISABLE_tolua_Binding_Window_ProcessEvents00
static int tolua_Binding_Window_ProcessEvents00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Window",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Window* self = (Window*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ProcessEvents'", NULL);
#endif
  {
   self->ProcessEvents();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ProcessEvents'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Render of class  Window */
#ifndef TOLUA_DISABLE_tolua_Binding_Window_Render00
static int tolua_Binding_Window_Render00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Window",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Window* self = (Window*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Render'", NULL);
#endif
  {
   self->Render();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Render'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: scene of class  Window */
#ifndef TOLUA_DISABLE_tolua_get_Window_scene_ptr
static int tolua_get_Window_scene_ptr(lua_State* tolua_S)
{
  Window* self = (Window*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scene'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->scene,"Node");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: scene of class  Window */
#ifndef TOLUA_DISABLE_tolua_set_Window_scene_ptr
static int tolua_set_Window_scene_ptr(lua_State* tolua_S)
{
  Window* self = (Window*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scene'",NULL);
  if (!tolua_isusertype(tolua_S,2,"Node",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->scene = ((Node*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Node */
#ifndef TOLUA_DISABLE_tolua_Binding_Node_new00
static int tolua_Binding_Node_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Node* tolua_ret = (Node*)  Mtolua_new((Node)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Node");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Node */
#ifndef TOLUA_DISABLE_tolua_Binding_Node_new00_local
static int tolua_Binding_Node_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Node* tolua_ret = (Node*)  Mtolua_new((Node)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Node");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Parent of class  Node */
#ifndef TOLUA_DISABLE_tolua_Binding_Node_Parent00
static int tolua_Binding_Node_Parent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Parent'", NULL);
#endif
  {
   Node* tolua_ret = (Node*)  self->Parent();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Node");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Parent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ChildCount of class  Node */
#ifndef TOLUA_DISABLE_tolua_Binding_Node_ChildCount00
static int tolua_Binding_Node_ChildCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ChildCount'", NULL);
#endif
  {
   size_t tolua_ret = (size_t)  self->ChildCount();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((size_t)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"size_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(size_t));
     tolua_pushusertype(tolua_S,tolua_obj,"size_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ChildCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Child of class  Node */
#ifndef TOLUA_DISABLE_tolua_Binding_Node_Child00
static int tolua_Binding_Node_Child00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Child'", NULL);
#endif
  {
   Node* tolua_ret = (Node*)  self->Child(i);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Node");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Child'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddChild of class  Node */
#ifndef TOLUA_DISABLE_tolua_Binding_Node_AddChild00
static int tolua_Binding_Node_AddChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  Node* node = ((Node*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddChild'", NULL);
#endif
  {
   self->AddChild(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveChild of class  Node */
#ifndef TOLUA_DISABLE_tolua_Binding_Node_RemoveChild00
static int tolua_Binding_Node_RemoveChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  Node* node = ((Node*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveChild'", NULL);
#endif
  {
   self->RemoveChild(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Unparent of class  Node */
#ifndef TOLUA_DISABLE_tolua_Binding_Node_Unparent00
static int tolua_Binding_Node_Unparent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Unparent'", NULL);
#endif
  {
   self->Unparent();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Unparent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Reparent of class  Node */
#ifndef TOLUA_DISABLE_tolua_Binding_Node_Reparent00
static int tolua_Binding_Node_Reparent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  Node* parent = ((Node*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Reparent'", NULL);
#endif
  {
   self->Reparent(parent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Reparent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Update of class  Node */
#ifndef TOLUA_DISABLE_tolua_Binding_Node_Update00
static int tolua_Binding_Node_Update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  double delta = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Update'", NULL);
#endif
  {
   self->Update(delta);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Render of class  Node */
#ifndef TOLUA_DISABLE_tolua_Binding_Node_Render00
static int tolua_Binding_Node_Render00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  Renderer* renderer = ((Renderer*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Render'", NULL);
#endif
  {
   self->Render(renderer);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Render'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Quad */
#ifndef TOLUA_DISABLE_tolua_Binding_Quad_new00
static int tolua_Binding_Quad_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Quad",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Quad* tolua_ret = (Quad*)  Mtolua_new((Quad)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Quad");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Quad */
#ifndef TOLUA_DISABLE_tolua_Binding_Quad_new00_local
static int tolua_Binding_Quad_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Quad",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Quad* tolua_ret = (Quad*)  Mtolua_new((Quad)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Quad");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Update of class  Quad */
#ifndef TOLUA_DISABLE_tolua_Binding_Quad_Update00
static int tolua_Binding_Quad_Update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Quad",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Quad* self = (Quad*)  tolua_tousertype(tolua_S,1,0);
  double delta = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Update'", NULL);
#endif
  {
   self->Update(delta);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Render of class  Quad */
#ifndef TOLUA_DISABLE_tolua_Binding_Quad_Render00
static int tolua_Binding_Quad_Render00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Quad",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Quad* self = (Quad*)  tolua_tousertype(tolua_S,1,0);
  Renderer* renderer = ((Renderer*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Render'", NULL);
#endif
  {
   self->Render(renderer);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Render'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Size of class  Quad */
#ifndef TOLUA_DISABLE_tolua_get_Quad_Size
static int tolua_get_Quad_Size(lua_State* tolua_S)
{
  Quad* self = (Quad*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Size'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->Size,"Vector2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Size of class  Quad */
#ifndef TOLUA_DISABLE_tolua_set_Quad_Size
static int tolua_set_Quad_Size(lua_State* tolua_S)
{
  Quad* self = (Quad*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Size'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Vector2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Size = *((Vector2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Shader of class  Quad */
#ifndef TOLUA_DISABLE_tolua_get_Quad_Shader
static int tolua_get_Quad_Shader(lua_State* tolua_S)
{
  Quad* self = (Quad*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Shader'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Shader);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Shader of class  Quad */
#ifndef TOLUA_DISABLE_tolua_set_Quad_Shader
static int tolua_set_Quad_Shader(lua_State* tolua_S)
{
  Quad* self = (Quad*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Shader'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Shader = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Texture of class  Quad */
#ifndef TOLUA_DISABLE_tolua_get_Quad_Texture
static int tolua_get_Quad_Texture(lua_State* tolua_S)
{
  Quad* self = (Quad*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Texture'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Texture);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Texture of class  Quad */
#ifndef TOLUA_DISABLE_tolua_set_Quad_Texture
static int tolua_set_Quad_Texture(lua_State* tolua_S)
{
  Quad* self = (Quad*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Texture'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Texture = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_Binding_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"Vector2","Vector2","",NULL);
  tolua_beginmodule(tolua_S,"Vector2");
   tolua_variable(tolua_S,"Zero",tolua_get_Vector2_Zero,NULL);
   tolua_variable(tolua_S,"One",tolua_get_Vector2_One,NULL);
   tolua_variable(tolua_S,"x",tolua_get_Vector2_x,tolua_set_Vector2_x);
   tolua_variable(tolua_S,"y",tolua_get_Vector2_y,tolua_set_Vector2_y);
   tolua_function(tolua_S,"Length",tolua_Binding_Vector2_Length00);
   tolua_function(tolua_S,"SquaredLength",tolua_Binding_Vector2_SquaredLength00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"App","App","",NULL);
  tolua_beginmodule(tolua_S,"App");
   tolua_function(tolua_S,"Instance",tolua_Binding_App_Instance00);
   tolua_function(tolua_S,"StartMainLoop",tolua_Binding_App_StartMainLoop00);
   tolua_function(tolua_S,"AddWindow",tolua_Binding_App_AddWindow00);
   tolua_function(tolua_S,"RemoveWindow",tolua_Binding_App_RemoveWindow00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Window","Window","",NULL);
  tolua_beginmodule(tolua_S,"Window");
   tolua_function(tolua_S,"Create",tolua_Binding_Window_Create00);
   tolua_function(tolua_S,"show",tolua_Binding_Window_show00);
   tolua_function(tolua_S,"ProcessEvents",tolua_Binding_Window_ProcessEvents00);
   tolua_function(tolua_S,"Render",tolua_Binding_Window_Render00);
   tolua_variable(tolua_S,"scene",tolua_get_Window_scene_ptr,tolua_set_Window_scene_ptr);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Node","Node","",tolua_collect_Node);
  #else
  tolua_cclass(tolua_S,"Node","Node","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Node");
   tolua_function(tolua_S,"new",tolua_Binding_Node_new00);
   tolua_function(tolua_S,"new_local",tolua_Binding_Node_new00_local);
   tolua_function(tolua_S,".call",tolua_Binding_Node_new00_local);
   tolua_function(tolua_S,"Parent",tolua_Binding_Node_Parent00);
   tolua_function(tolua_S,"ChildCount",tolua_Binding_Node_ChildCount00);
   tolua_function(tolua_S,"Child",tolua_Binding_Node_Child00);
   tolua_function(tolua_S,"AddChild",tolua_Binding_Node_AddChild00);
   tolua_function(tolua_S,"RemoveChild",tolua_Binding_Node_RemoveChild00);
   tolua_function(tolua_S,"Unparent",tolua_Binding_Node_Unparent00);
   tolua_function(tolua_S,"Reparent",tolua_Binding_Node_Reparent00);
   tolua_function(tolua_S,"Update",tolua_Binding_Node_Update00);
   tolua_function(tolua_S,"Render",tolua_Binding_Node_Render00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Quad","Quad","Node",tolua_collect_Quad);
  #else
  tolua_cclass(tolua_S,"Quad","Quad","Node",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Quad");
   tolua_function(tolua_S,"new",tolua_Binding_Quad_new00);
   tolua_function(tolua_S,"new_local",tolua_Binding_Quad_new00_local);
   tolua_function(tolua_S,".call",tolua_Binding_Quad_new00_local);
   tolua_function(tolua_S,"Update",tolua_Binding_Quad_Update00);
   tolua_function(tolua_S,"Render",tolua_Binding_Quad_Render00);
   tolua_variable(tolua_S,"Size",tolua_get_Quad_Size,tolua_set_Quad_Size);
   tolua_variable(tolua_S,"Shader",tolua_get_Quad_Shader,tolua_set_Quad_Shader);
   tolua_variable(tolua_S,"Texture",tolua_get_Quad_Texture,tolua_set_Quad_Texture);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_Binding (lua_State* tolua_S) {
 return tolua_Binding_open(tolua_S);
};
#endif

