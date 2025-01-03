#include "PreCompiledHeader.h"
#include "Engine.h"
#include <Level/Level.h>

// 스태틱 변수 초기하
Engine* Engine::instance = nullptr;

Engine::Engine()
	: quit(0), mainLevel(nullptr)
{
	// 싱글톤 객체 설정
	instance = this;
}

Engine::~Engine()
{
	// 메인 레벨 해제.
	if (mainLevel != nullptr)
	{
		delete mainLevel;
	}
}

void Engine::Run()
{
	//// 시작 타임 스탬프 저장. timeGetTime() ms를 리턴한다.
	// timeGetTime 함수는 밀리세컨드 단위. (1 / 1,000) -> 부정확함.
	//unsigned long currentTime = timeGetTime();
	//unsigned long previousTime = 0;

	// CPU 시계 사용
	// 시스템 시계 -> 고해상도 카운터. (1 / 10,000,000).
	// 메인보드에 시계가 있음.
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	// 시작 시간 및 이전 시간을 위한 변수
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	int64_t currentTime = time.QuadPart;
	int64_t previousTime = 0;

	// 프레임 제한
	float targetFrameRate = 60.0f;

	// 한 프레임 시간 계산
	float targetOneFrameTime = 1.0f / targetFrameRate;


	// Game-Loop
	while (true)
	{
		// 종료 조건
		if (quit) break;

		// 현재 프레임 시간 저장.
		//currentTime = timeGetTime();
		QueryPerformanceCounter(&time);
		currentTime = time.QuadPart;

		// 프레임 시간 계산.
		float deltaTime = static_cast<float>(currentTime - previousTime) / static_cast<float>(frequency.QuadPart);

		
		// 프레임 확인.
		if (deltaTime >= targetOneFrameTime)
		{
			// 입력 처리 (현재 키의 눌림 상태 확인).
			ProcessInput();

			Update(deltaTime);
			Draw();

			// 키 상태 저장
			SavePreviousKeySates();

			// 이전 프레임 시간 저장
			previousTime = currentTime;
		}

		// 프레임 속도가 너무 빠를 때
		// Sleep(1);
	}
}

void Engine::LoadLevel(Level* newLevel)
{
	// 기존 레벨이 있다면 삭제 후 교체.

	// 메인 레벨 설정
	mainLevel = newLevel;
}

bool Engine::GetKey(int key)
{
	return keyState[key].isKeyDown;
}

bool Engine::GetKeyDown(int key)
{
	return keyState[key].isKeyDown && !keyState[key].wasKeyDown;
}

bool Engine::GetKeyUp(int key)
{
	return !keyState[key].isKeyDown && keyState[key].wasKeyDown;
}

void Engine::QuitGame()
{
	quit = true;
}

Engine& Engine::Get()
{
	// 싱글톤 객체 반환
	return *instance;
}

void Engine::ProcessInput()
{
	for (int i = 0; i < 255; ++i)
	{
		keyState[i].isKeyDown = (GetAsyncKeyState(i) & 0x8000) ? true : false;
	}
}

void Engine::Update(float deltaTime)
{
	// 레벨 업데이트.
	if (mainLevel != nullptr)
	{
		mainLevel->UpDate(deltaTime);
	}
}

void Engine::Draw()
{
	// 레벨 그리기
	if (mainLevel != nullptr)
	{
		mainLevel->Draw();
	}
}

void Engine::SavePreviousKeySates()
{
	for (int i = 0; i < 255; ++i)
	{
		keyState[i].wasKeyDown = keyState[i].isKeyDown;
	}
}