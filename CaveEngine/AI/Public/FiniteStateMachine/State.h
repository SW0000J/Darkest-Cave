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
		State(std::string stateName);
		State(std::string stateName, char trigger);
		State(std::string stateName, char trigger, int Animation);
		// animation �߰�
		// �̸��߰�
		virtual ~State();
		void LinkState(State* state);
		void setAnimation(int animation);
		void setCurrentState();
		void cancelCurrentState();
		State* searchNewCurrentState(char trigger);
		void updateState(State* newCurrentState);
		std::string getStateName();
		char getTrigger();
		void setBool(bool boolState);
		int showAnimation();
		
	private:
		int mAnimation;
		bool mIsCurrent;
		char mTrigger;
		std::string mStateName;
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
