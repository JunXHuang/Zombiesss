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
	this:setVelocity(jumpVelocityX, jumpVelocityY);
	
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

function moveBot(player)
	local playerLocX = player:getX();
	if (this:getX() <= (playerLocX + 300) and this:getX() >= (playerLocX - 300)) then
		if (this:getX() > playerLocX) then
			this:setVelocity(-10, 0);
		else
			this:setVelocity(10, 0);
		end
	end
end

--[[
	think - called once per frame, this is where the bot performs its
	decision-making. Note that we might not actually do any thinking each
	frame, depending on the value of cyclesRemainingBeforeThinking.
--]]
function think(player)
	-- EACH FRAME WE'LL TEST THIS BOT TO SEE IF WE NEED
	-- TO PICK A DIFFERENT DIRECTION TO FLOAT IN

	moveBot(player);
	if cyclesRemainingBeforeThinking == 0 then
		--pickRandomJump();
		pickRandomCyclesInRange();
	else
		cyclesRemainingBeforeThinking = cyclesRemainingBeforeThinking - 1;
	end
	
	return 0;
end