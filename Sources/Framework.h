#pragma once

#include "BaseObject.h"
class Framework : public BaseObject
{
public:
	Framework();
	~Framework();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() override;

protected:
	virtual void Release() override;
};

