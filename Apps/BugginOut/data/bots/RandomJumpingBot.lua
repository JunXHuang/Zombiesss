cyclesRemainingBeforeThinking = 30;
-- INIT OUR RANGE VARIABLES
minCyclesBeforeThinking = tonumber(initMin);
maxCyclesBeforeThinking = tonumber(initMax);
-- AND OUR VELOCITY CAPPER
maxVelocity = tonumber(initVel);

--[[
	pickRandomCyclesInRange - a randomized method for determining when this bot
	will think again. This method sets that value.
--]]
function pickRandomCyclesInRange()
	local difference = math.random() * (maxCyclesBeforeThinking - minCyclesBeforeThinking + 1);
	cyclesRemainingBeforeThinking = minCyclesBeforeThinking + math.floor(difference);
	
	return 0;
end

--[[
	pickRandomVelocity - calculates a random velocity vector for this
	bot and initializes the appropriate instance variables.
--]]
function pickRandomJump()
	-- PICK A RANDOM JUMPING ANGLE
	local randomAngleInRadians = (math.random() * math.pi/6.0) + (math.pi*2.5/6.0);

	-- NOW WE CAN SCALE OUR X AND Y VELOCITIES
	local jumpVelocity = maxVelocity;
	local jumpVelocityX = jumpVelocity * math.cos(randomAngleInRadians);
	local jumpVelocityY = -jumpVelocity * math.sin(randomAngleInRadians);
	this:setVelocity(jumpVelocityX*(math.random()%3+1), 0);
	
	return 0;
end

--[[
	init - called once when the bot is created, this sets up the local
	variables and performs other initialization procedures.
--]]
function init()
	if minCyclesBeforeThinking < maxCyclesBeforeThinking then
		local temp = maxCyclesBeforeThinking;
		maxCyclesBeforeThinking = minCyclesBeforeThinking;
		minCyclesBeforeThinking = temp;
	elseif maxCyclesBeforeThinking == minCyclesBeforeThinking then
		-- IF THEY ARE THE SAME, ADD 100 CYCLES TO THE MAX
		maxCyclesBeforeThinking = maxCyclesBeforeThinking + 100;
	end
	
	return 0;
end

--[[
	think - called once per frame, this is where the bot performs its
	decision-making. Note that we might not actually do any thinking each
	frame, depending on the value of cyclesRemainingBeforeThinking.
--]]
function think(player)
	-- EACH FRAME WE'LL TEST THIS BOT TO SEE IF WE NEED
	-- TO PICK A DIFFERENT DIRECTION TO FLOAT IN
	local playerLocX = player:getX();
	local inRange = false;
	if (this:getX() <= (playerLocX + 500) and this:getX() >= (playerLocX - 500)) then
		--move zombie
		if (this:getX() > playerLocX) then
			this:setVelocity(-10, this:getVelocityY());
		else
			this:setVelocity(10, this:getVelocityY());
		end
		inRange = true;
	else
		this:setVelocity(0, this:getVelocityY());
	end
	
	if cyclesRemainingBeforeThinking == 0 then
		--pickRandomJump();
		pickRandomCyclesInRange();
		--spawn ball
		if (inRange == true) then
			SpawnBall();
		end
	else
		cyclesRemainingBeforeThinking = cyclesRemainingBeforeThinking - 1;
	end
	
	return 0;
end