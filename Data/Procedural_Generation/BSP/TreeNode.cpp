#include<iostream>
#include<random>
#include"TreeNode.h"

void TreeNode::setRoot(int** _map, int _height, int _width) {
	this->info.height = _height;
	this->info.width = _width;
	this->info.points_x = 0;
	this->info.points_y= 0;

	// �ڽ�, �θ� ��� �ʱ�ȭ
	this->leftNode = NULL;
	this->rightNode = NULL;
	this->parentNode = NULL;
}

void TreeNode::devide_col(int** _map) {
	//�յ� ���� ���� �� ũ���� 30% ~ 70%
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(this->info.width * 3 / 10, this->info.width * 7 / 10);

	int _height = this->info.height;
	int _width = dis(gen);

	// ���� �ڽ� ��� �ʱ�ȭ
	this->leftNode = new TreeNode;
	this->leftNode->info.height = _height;
	this->leftNode->info.width = _width;
	this->leftNode->info.points_x = this->info.points_x;
	this->leftNode->info.points_y = this->info.points_y;
	this->leftNode->parentNode = this;
	this->leftNode->info.parent_devide_type = 0;

	// ������ �ڽ� ��� �ʱ�ȭ
	this->rightNode = new TreeNode;
	this->rightNode->info.height = this->info.height;
	this->rightNode->info.width = this->info.width - _width + 1;
	this->rightNode->info.points_x = this->info.points_x + _width - 1;
	this->rightNode->info.points_y = this->info.points_y;
	this->rightNode->parentNode = this;
	this->rightNode->info.parent_devide_type = 0;

	// ��輱 �߱�
	for (int i = this->info.points_y + 1; i < this->info.points_y + this->info.height - 1; i++) {
		_map[i][this->info.points_x + _width - 1] = 1;
	}
}

void TreeNode::devide_row(int** _map) {
	//�յ� ���� ���� �� ũ���� 30% ~ 70%
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(this->info.height * 3 / 10, this->info.height * 7 / 10);
	
	int _height = dis(gen);
	int _width = this->info.width;

	// ���� �ڽ� ��� �ʱ�ȭ
	this->leftNode = new TreeNode;
	this->leftNode->info.height = _height + 1;
	this->leftNode->info.width = _width;
	this->leftNode->info.points_x = this->info.points_x;
	this->leftNode->info.points_y = this->info.points_y;
	this->leftNode->parentNode = this;
	this->leftNode->info.parent_devide_type = 1;

	// ������ �ڽ� ��� �ʱ�ȭ
	this->rightNode = new TreeNode;
	this->rightNode->info.height = this->info.height - _height;
	this->rightNode->info.width = this->info.width;
	this->rightNode->info.points_x = this->info.points_x;
	this->rightNode->info.points_y = this->info.points_y + _height;
	this->rightNode->parentNode = this;
	this->rightNode->info.parent_devide_type = 1;

	// ��輱 �߱�
	for (int i = this->info.points_x; i < this->info.points_x + this->info.width; i++) {
		_map[this->info.points_y + _height][i] = 1;
	}
}

TreeNode* TreeNode::goLeftNode() {
	return this->leftNode;
}

TreeNode* TreeNode::goRightNode() {
	return this->rightNode;
}

int TreeNode::getHeight() {
	return this->info.height;
}
int TreeNode::getWidth() {
	return this->info.width;
}

int TreeNode::getX() {
	return this->info.points_x;
}
int TreeNode::getY() {
	return this->info.points_y;

}

void TreeNode::allocateRoom(int** _map) {
	// ������ 1,2,3ĭ ������
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(2,3);

	int start_h = this->info.points_y + dis(gen);
	int end_h = this->info.points_y + this->info.height - dis(gen);

	int start_w = this->info.points_x + dis(gen);
	int end_w = this->info.points_x + this->info.width - dis(gen);

	this->info.room_points_x = start_w;
	this->info.room_points_y = start_h;
	this->info.room_height = end_h - start_h;
	this->info.room_width = end_w - start_w;

	for (int i = start_h; i < end_h; i++) {
		for (int j = start_w; j < end_w; j++) {
			_map[i][j] = 2;
		}
	}
}

void TreeNode::connectRoom(int** _map, TreeNode* room1, TreeNode* room2) {
	if (room1->parentNode == room2->parentNode) {
		if (room1->info.parent_devide_type == 0) {
			// ��ġ�� �κ� ã��(Y��ǥ)
			int overlap_y_start;
			int overlap_y_end;
			for (int i = room2->info.room_points_y; i < room2->info.room_points_y + room2->info.room_height; i++) {
				if (i >= room1->info.room_points_y && i < room1->info.room_points_y + room1->info.room_height) {
					overlap_y_start = i;
					break;
				}
			}
			for (int i = overlap_y_start; i < room2->info.room_points_y + room2->info.room_height; i++) {
				if (i >= room1->info.room_points_y + room1->info.room_height) {
					overlap_y_end = i - 1;
					break;
				}
				overlap_y_end = i;
			}
			
			for (int i = room1->info.room_points_x + room1->info.room_width; i < room2->info.room_points_x; i++) {
				_map[(overlap_y_start + overlap_y_end) / 2 - 1][i] = 3;
				_map[(overlap_y_start + overlap_y_end) / 2][i] = 3;
				_map[(overlap_y_start + overlap_y_end) / 2 + 1][i] = 3;
			}
		}
		else {
			// ��ġ�� �κ� ã��(X��ǥ)
			int overlap_x_start;
			int overlap_x_end;
			for (int i = room2->info.room_points_x; i < room2->info.room_points_x + room2->info.room_width; i++) {
				if (i >= room1->info.room_points_x && i < room1->info.room_points_x + room1->info.room_width) {
					overlap_x_start = i;
					break;
				}
			}
			for (int i = overlap_x_start; i < room2->info.room_points_x + room2->info.room_width; i++) {
				if (i >= room1->info.room_points_x + room1->info.room_width) {
					overlap_x_end = i - 1;
					break;
				}
				overlap_x_end = i;
			}

			for (int i = room1->info.room_points_y + room1->info.room_height; i < room2->info.room_points_y; i++) {
				_map[i][(overlap_x_start + overlap_x_end) / 2 - 1] = 3;
				_map[i][(overlap_x_start + overlap_x_end) / 2] = 3;
				_map[i][(overlap_x_start + overlap_x_end) / 2 + 1] = 3;
			}
		}
	}
	else {
		// �θ�鵵 �̾�� ��
	}
}

void TreeNode::connectRoom_Y(int** _map, TreeNode* room1, TreeNode* room2) {
	// ��ġ�� �κ� ã��(X��ǥ)
	int overlap_x_start;
	int overlap_x_end;
	for (int i = room2->info.room_points_x; i < room2->info.room_points_x + room2->info.room_width; i++) {
		if (i >= room1->info.room_points_x && i < room1->info.room_points_x + room1->info.room_width) {
			overlap_x_start = i;
			break;
		}
	}
	for (int i = overlap_x_start; i < room2->info.room_points_x + room2->info.room_width; i++) {
		if (i >= room1->info.room_points_x + room1->info.room_width) {
			overlap_x_end = i - 1;
			break;
		}
		overlap_x_end = i;
	}

	for (int i = room1->info.room_points_y + room1->info.room_height; i < room2->info.room_points_y; i++) {
		_map[i][(overlap_x_start + overlap_x_end) / 2 - 1] = 3;
		_map[i][(overlap_x_start + overlap_x_end) / 2] = 3;
		_map[i][(overlap_x_start + overlap_x_end) / 2 + 1] = 3;
	}
}

void TreeNode::connectRoom_X(int** _map, TreeNode* room1, TreeNode* room2) {
	// ��ġ�� �κ� ã��(Y��ǥ)
	int overlap_y_start;
	int overlap_y_end;
	for (int i = room2->info.room_points_y; i < room2->info.room_points_y + room2->info.room_height; i++) {
		if (i >= room1->info.room_points_y && i < room1->info.room_points_y + room1->info.room_height) {
			overlap_y_start = i;
			break;
		}
	}
	for (int i = overlap_y_start; i < room2->info.room_points_y + room2->info.room_height; i++) {
		if (i >= room1->info.room_points_y + room1->info.room_height) {
			overlap_y_end = i - 1;
			break;
		}
		overlap_y_end = i;
	}

	for (int i = room1->info.room_points_x + room1->info.room_width; i < room2->info.room_points_x; i++) {
		_map[(overlap_y_start + overlap_y_end) / 2 - 1][i] = 3;
		_map[(overlap_y_start + overlap_y_end) / 2][i] = 3;
		_map[(overlap_y_start + overlap_y_end) / 2 + 1][i] = 3;
	}
}

// �� ���� ���� ����Ʈ
void TreeNode::printInfo() {
	std::cout << "�� ����: " << this->info.height << std::endl;
	std::cout << "�� ����: " << this->info.width << std::endl;
	std::cout << "�� x��ǥ: " << this->info.points_x << std::endl;
	std::cout << "�� y��ǥ: " << this->info.points_y << std::endl;
	/*
	if (this->leftNode != NULL) {
		std::cout << "���� �ڽ� �� ����: " << this->leftNode->info.height << std::endl;
		std::cout << "���� �ڽ� �� ����: " << this->leftNode->info.width << std::endl;
		std::cout << "���� �ڽ� �� x��ǥ: " << this->leftNode->info.points_x << std::endl;
		std::cout << "���� �ڽ� �� y��ǥ: " << this->leftNode->info.points_y << std::endl;
	}
	
	if (this->rightNode != NULL) {
		std::cout << "������ �ڽ� �� ����: " << this->rightNode->info.height << std::endl;
		std::cout << "������ �ڽ� �� ����: " << this->rightNode->info.width << std::endl;
		std::cout << "������ �ڽ� �� x��ǥ: " << this->rightNode->info.points_x << std::endl;
		std::cout << "������ �ڽ� �� y��ǥ: " << this->rightNode->info.points_y << std::endl;
	}
	*/
}

// �� �Ҵ�� ���� ���� ����Ʈ
void TreeNode::printRoomInfo() {
	std::cout << "�Ҵ�� �� ����: " << this->info.room_height << std::endl;
	std::cout << "�Ҵ�� �� ����: " << this->info.room_width << std::endl;
	std::cout << "�Ҵ�� �� x��ǥ: " << this->info.room_points_x << std::endl;
	std::cout << "�Ҵ�� �� y��ǥ: " << this->info.room_points_y << std::endl;
}