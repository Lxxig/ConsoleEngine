#pragma once


// ������ �⺻ ��ü.
class ENGINE_API Actor
{
public:
	Actor();
	virtual ~Actor();

	virtual void UpDate(float deltaTime);
	virtual void Draw();

protected:
	// ID(�ؽ�) / �̸� ��.

	// Ȱ��ȭ ���������� ��Ÿ���� ����.
	bool isActive;

	// ������ ���� ��û�� �ƴ��� ���θ� ��Ÿ���� ����.
	bool isExpired;

};
