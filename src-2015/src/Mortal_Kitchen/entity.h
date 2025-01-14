// Sylvain.Lefebvre@inria.fr  2015-03-24
#pragma once

// ------------------------------------------------------------------

#include<string>

using namespace std;

// ------------------------------------------------------------------

#include "drawimage.h"
#include "script.h"
#include "physics.h"

// ------------------------------------------------------------------

typedef struct {
  DrawImage *animframes;
  int        framespacing;
  int        numframes;
  int        delay;
} SpriteAnim;

// ------------------------------------------------------------------

typedef struct
{
  string                   name;
  map<string, SpriteAnim*> anims;

  string                   currentAnim;
  int                      currentFrame;
  time_t                   lastAnimUpdate;
  bool                     animIsPlaying;
  bool                     animIsALoop;

  // v2f                      pos; ==> this is now in the physics body
  bool                     killed;

  Script                  *script;                    

  b2Body                  *body;

  //life
  bool					   alive;
  int					   life;

  int                      damage;
  float                    push;
  string                   owner;

  int                      x_init;
  
} Entity;

// ------------------------------------------------------------------

Entity *entity_create(string fname, string script);
Entity *entity_createStatic(int w, int h);
void    entity_draw(Entity *e, v2i viewpos);
void    entity_step(Entity *e, time_t elapsed);
void    entity_contact(Entity *e,Entity *with);
void    entity_onfloor(Entity *e);
AAB<2>  entity_bbox(Entity *e);
void    apply_damage(Entity *with, Entity *from);
void    lua_attack(string filename, string owner, string side, int posx, int posy);

v2f     entity_get_pos(Entity *e);
float   entity_get_angle(Entity *e);
void    entity_set_pos(Entity *e,v2f p);

// ------------------------------------------------------------------











