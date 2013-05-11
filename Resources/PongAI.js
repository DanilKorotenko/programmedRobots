var lastBallY = 0;
var lastBallDistance = 0;

function nextMove(paddle, ball)
{
	var ballY = ball.middleY;
	var ballX = ball.middleX;
	var paddleX = paddle.middleX;

	var ballDistance = 0;

	if (paddleX > ballX)
	{
		ballDistance = paddleX - ballX;
	}
	else
	{
		ballDistance = ballX - paddleX;
	}

	if (lastBallDistance != 0)
	{
		if (ballDistance > lastBallDistance)
		{
			lastBallDistance = ballDistance
			return kStationaryDirection;
		}
	}

	lastBallDistance = ballDistance;

	var ballDirection = ballY < lastBallY
		? kUpDirection
		: kDownDirection;
	lastBallY = ballY;

	if (ballY < paddle.top)
		return kUpDirection;

	if (ballY > paddle.bottom)
		return kDownDirection;

	return ballDirection;
}
