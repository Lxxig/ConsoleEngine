#include "PreCompiledHeader.h"
#include "Level.h"
//#include "../Actor/Actor.h" 
// �Ӽ� -> c++ -> �Ϲ� -> �߰����� ���͸� -> $(ProjectDir)\;
#include <Actor/Actor.h>

Level::Level()
	: actors(nullptr), capacity(4), count(0)
{
	// ���� �迭 ����
	actors = new Actor * [capacity];

	// �ʱ�ȭ
	memset(actors, 0, sizeof(size_t) * capacity);
}

Level::~Level()
{
	// �޸� ����
	for (int i = 0; i < count; ++i)
	{
		// ���� ����.
		delete actors[i];
	}

	// ���� �迭 ����;
	delete[] actors;
}

void Level::AddActor(Actor* newActor)
{
	// ���� �Ҵ�� ������ ������� Ȯ��.
	if (count == capacity)
	{
		// ���� �߰� �Ҵ�.
		int newCapacity = capacity * 2;
		
		// �ӽ� ����
		Actor** temp = new Actor * [newCapacity];

		// ������ ���� ����.
		// loop�� �ϵ���.
		memcpy(temp, actors, sizeof(size_t) * capacity);

		// ���� �迭 ����.
		delete[] actors;

		// �迭 ��ü
		actors = temp;
		// temp = nullptr;

		// ũ�� ����.
		capacity = newCapacity;
	}

	// ���� �߰�.
	actors[count] = newActor;
	count++;
}

void Level::UpDate(float deltaTime)
{
	// ������ ���Ե� ���͸� ��ȸ�ϸ鼭 Update �Լ� ȣ��.
	for (int i = 0; i < count; ++i)
	{
		actors[i]->UpDate(deltaTime);
	}
}

void Level::Draw()
{
	// ������ ���Ե� ���͸� ��ȸ�ϸ鼭 Draw �Լ� ȣ��.
	for (int i = 0; i < count; ++i)
	{
		actors[i]->Draw();
	}
}