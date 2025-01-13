#include "PreCompiledHeader.h"
#include "DrawableActor.h"
#include "Engine/Engine.h"

DrawableActor::DrawableActor(char image)
	: Actor(), image(image)
{
}

void DrawableActor::Draw()
{
	Super::Draw();

	// �׸���.
	// 1�ܰ�: �ܼ� ��ǥ �ű��.
	Engine::Get().SetCursorPosition(position);

	// 2�ܰ�: �׸��� (�ܼ� ���).
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	Log("%c", image);
}

void DrawableActor::SetPosition(const Vector2& newPosition)
{
	// ������ ��ġ�� ���� �����.
	Engine::Get().SetCursorPosition(position);
	Log(" ");

	// ��ġ�� ���� �ű��.
	Super::SetPosition(newPosition);
}