/*
 * ExceptionScreen.cpp
 *
 *  Created on: 13 ����. 2017 �.
 *      Author: �������
 */

#include "ExceptionScreen.h"

void showExceptionScreen(){
	system("cls");
	cout<<"������ ����� ������! ���������� ��� ���!"<<endl;
	system("pause");
}

void showNotFindData(){
	system("cls");
	cout<<"�� ������ ������� ������ �� ����������! ���������� ��� ���!"<<endl;
	system("pause");
}

void showNotData(){
	system("cls");
	cout<<"������ ��� � ���� ������! ��� ����������� �����������!"<<endl;
	system("pause");
}

void showNotFindUserId(unsigned int UserId){
	system("cls");
	cout<<"������������ � ����� ID = " << UserId << " ��� � ���� ������!"<<endl;
	system("pause");
}

void showNotCompDate(){
	system("cls");
	cout<<"����������� ���� ����� �� ����� ���� ������ ���� ������ �������" <<endl;
	system("pause");
}

void showNotPlannedDate(){
	system("cls");
	cout << "����� ����� ������� ���������� �� ���� ������� ���������� � ��������������" <<endl;
	system("pause");
}
