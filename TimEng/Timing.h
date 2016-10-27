#pragma once

namespace TimEng{

	class FpsLimiter{
	public:
		FpsLimiter();
		void init(float _maxfps);

		void setMaxFPS(float _maxfps);

		void begin();

		//Will return the fps
		float end();

	private:
		void calculateFPS();

		float _fps;
		float _maxfps;
		float _frameTime;

		unsigned int _startTicks;
	};

}