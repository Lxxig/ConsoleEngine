#include "PreCompiledHeader.h"
#include "Level.h"
//#include "../Actor/Actor.h" 
// 속성 -> c++ -> 일반 -> 추가포함 디렉터리 -> $(ProjectDir)\;
#include <Actor/Actor.h>

Level::Level()
	: actors(nullptr), capacity(4), count(0)
{
	// 동적 배열 생성
	actors = new Actor * [capacity];

	// 초기화
	memset(actors, 0, sizeof(size_t) * capacity);
}

Level::~Level()
{
	// 메모리 해제
	for (int i = 0; i < count; ++i)
	{
		// 액터 삭제.
		delete actors[i];
	}

	// 동적 배열 해제;
	delete[] actors;
}

void Level::AddActor(Actor* newActor)
{
	// 현재 할당된 공간이 충분한지 확인.
	if (count == capacity)
	{
		// 공간 추가 할당.
		int newCapacity = capacity * 2;
		
		// 임시 공간
		Actor** temp = new Actor * [newCapacity];

		// 기존의 값을 복사.
		// loop로 하도됨.
		memcpy(temp, actors, sizeof(size_t) * capacity);

		// 기존 배열 삭제.
		delete[] actors;

		// 배열 교체
		actors = temp;
		// temp = nullptr;

		// 크기 변경.
		capacity = newCapacity;
	}

	// 액터 추가.
	actors[count] = newActor;
	count++;
}

void Level::UpDate(float deltaTime)
{
	// 레벨에 포함된 액터를 순회하면서 Update 함수 호출.
	for (int i = 0; i < count; ++i)
	{
		actors[i]->UpDate(deltaTime);
	}
}

void Level::Draw()
{
	// 레벨에 포함된 액터를 순회하면서 Draw 함수 호출.
	for (int i = 0; i < count; ++i)
	{
		actors[i]->Draw();
	}
}
