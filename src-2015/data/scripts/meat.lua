physics_center_x  = 0
physics_center_y  = 0
physics_size_x    = 18
physics_size_y    = 18
physics_can_sleep = true
physics_rotation  = true
is_movable        = true
damage            = 50
push              = 1.0
range             = 3
density           = 2
speed_x           = 6
speed_y           = 4
last_pos_x        = 0

addanim('meat.png',45,100)
playanim('meat.png',false)

initialized = false

function step()

end

function contact(with)
  if with == 'player' then
	son = {"ouille.wav","aieaieaie.wav"}
	playsound(son[math.random(1,2)])
  end 
end

function onAnimEnd()
  playanim('meat.png',false)
end

function onFloor()
	killed = true
end