#pragma once

struct Info
{
	// ���� ����
	int height;
	int width;
	int points_x; // x��ǥ
	int points_y; // y��ǥ

	// �� ����
	int room_height;
	int room_width;
	int room_points_x; // x��ǥ
	int room_points_y; // y��ǥ

	int parent_devide_type; // �θ� ��� �� �� � �������� ���������� ��Ÿ��. 0�̸� ��, 1�̸� ������ ����.
};

class TreeNode {
private:
	TreeNode* leftNode;
	TreeNode* rightNode;
	TreeNode* parentNode;
	Info info;
public:
	void setRoot(int** _map, int _height, int _width);
	void devide_col(int** _map);
	void devide_row(int** _map);

	TreeNode* goRoot();
	TreeNode* goLeftNode();
	TreeNode* goRightNode();

	int getHeight();
	int getWidth();
	int getX();
	int getY();

	void allocateRoom(int** _map);
	void connectRoom(int** _map, TreeNode* room1, TreeNode* room2);
	void connectRoom_X(int** _map, TreeNode* room1, TreeNode* room2);
	void connectRoom_Y(int** _map, TreeNode* room1, TreeNode* room2);

	void devide(int** _map, int _numOfRoom);

	void printInfo();
	void printRoomInfo();
};