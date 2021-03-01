﻿#pragma once
#include "Subject.h"

namespace dae
{
	class Component :public Subject
	{
	public:



		virtual void Update() = 0;
		virtual void Render() const {}


		Component() = default;
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

	};
}
