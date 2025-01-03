#pragma once

// 전방선언
class Actor;
class ENGINE_API Level
{
public:
	Level();
	virtual ~Level();

	// 액터 추가 함수.
	void AddActor(Actor* newActor);

	// 루프 처리 함수.
	virtual void UpDate(float deltaTime);
	virtual void Draw();

protected:
	// 게임 공간에 배치되는 물체(액터) 배열
	Actor** actors;

	// 저장할 수 잇는 공간의 크기
	int capacity;

	// 현재 레벨에 추가된 액터의 수
	int count;
};

