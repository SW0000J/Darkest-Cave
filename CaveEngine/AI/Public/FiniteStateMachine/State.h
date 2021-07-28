/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <iostream>
#include <vector>

namespace cave
{
	class State
	{
	public:
		State();
		State(bool Animation);
		LinkState(State state);
		virtual ~State();
		
	private:
		bool mAnimation;
		std::vector<State*> mNeighborState;

	};
}

// fsm �� ������ �������� ���� ��, trigger �޹� (int, float, bool �پ�)
// map �������� isJump == true, false
// root node �ϳ� �ʿ�, �׷����� ������ �⺻���� �ƴ�
// root ==> idle (������ ���ִ� ����)
// idle -> jump, idle -> jump 
// ������ ��� Ž��, �´°� ������ �Ѿ�� ����
// such as bfs
