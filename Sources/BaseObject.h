#pragma once
class BaseObject
{
public:
	BaseObject();
	~BaseObject();

public:
	virtual void Initialize() abstract;
	virtual void Update() abstract;
	virtual void Render() abstract;

protected:
	virtual void Release() abstract;
};