physics_center_x  =  0
physics_center_y  =  0
stand_size_x    = 35
stand_size_y    = 120
crouch_size_x    = 45
crouch_size_y    = 80
physics_size_x    = stand_size_x
physics_size_y    = stand_size_y
density           = 5
physics_can_sleep = false
physics_rotation  = false
is_movable        = true

-- define a state variable which can be: 
-- 'wait_left', 'wait_right'
-- 'walk_left', 'walk_right'
-- 'turn_left', 'turn_right'

state = 'wait'
side = 'left'
player = 'sergio.'
separator = '.'
on_floor = true

addanim(player .. 'walk'..separator..'left.png',256,75) --75ms between frames, sergio is the fastest
addanim(player .. 'walk'..separator..'right.png',256,75)
addanim(player .. 'crouch'..separator..'left.png',256,75)
addanim(player .. 'crouch'..separator..'right.png',256,75)
addanim(player .. 'fight'..separator..'right.png',320,50)
addanim(player .. 'fight'..separator..'left.png',320,50)
addanim(player .. 'jump'..separator..'right.png',256,75)
addanim(player .. 'jump'..separator..'left.png',256,75)

playanim(player .. 'walk'..separator..'left.png',true)
stopanim()

function step()

	if state == 'wait' then
		if Key_q then
			state = 'walk'
			side = 'left'
			playanim(player .. state .. separator .. side .. '.png',true)
		end
		if Key_d then
			state = 'walk'
			side = 'right'
			playanim(player .. state .. separator .. side .. '.png',true)
		end

		if Key_s then
			state = 'crouch'
			physics_size_x    = crouch_size_x
			physics_size_y    = crouch_size_y
			set_y(pos_y - (stand_size_y - crouch_size_y))
			reset_box()
			playanim(player .. state .. separator .. side .. '.png',true)
		end
		if Key_g and on_floor then
			state = 'fight'
			son = {"ha.wav","pipou.wav"}
			playsound(son[math.random(1,2)])
			playanim(player .. state .. separator .. side .. '.png',false)
			
			-- attack
			coef = 1
			if side == "left" then
				coef = -1
			end
			attack('sergio_punch.lua',name, side, pos_x + coef * physics_size_x, pos_y + 45)
		end 
	end
	
	if state == 'jump' and not(on_floor) then
		if Key_q then
			side = 'left'
			set_velocity_x(-2.2)
			playanim(player .. state .. separator .. side .. '.png',true)
		end
		if Key_d then
			side = 'right'
			set_velocity_x(2.2)
			playanim(player .. state .. separator .. side .. '.png',true)
		end
	end
	
	-- reset states
	if state == 'walk' and not Key_q and not Key_d then
		state = 'wait'
		stopanim()
	end
	
	if state == 'crouch' and not Key_s then
		physics_size_x    = stand_size_x
        physics_size_y    = stand_size_y
		set_y(pos_y + (stand_size_y - crouch_size_y))
		reset_box()
		state = 'wait'
		playanim(player .. 'walk' .. separator .. side .. '.png',true) --get up
		stopanim()
	end

	if Key_z and on_floor then
		set_velocity_y(6.0)
		on_floor = false
		state='jump'
		-- play jump anim not a loop
		playanim(player .. state .. separator .. side .. '.png',false)
		playsound("boing.wav")
	end

	-- walk if state is 'walk_*'
	if state == 'walk' then 
		factor = 1
		if side == 'left' then
			factor = -1
		end
		set_velocity_x(factor * 2.2)
	end
end

function contact(with)
	
end

function onFloor()
	on_floor = true
	if state=='jump' then 
		state='walk'
		playanim(player .. state .. separator .. side .. '.png',true)
	end
end

function onAnimEnd()
  if state == 'fight' then
	state = 'wait'
  end
end
