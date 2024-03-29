#ifndef _RESOURCE_H
#define _RESOURCE_H

#define IDC_BUTTON_LOAD_DATA 1000
#define IDC_BUTTON_ADD_ITEM 1001
#define IDC_BUTTON_REPORT 1002
#define IDC_BUTTON_DEL_SELECTED 1003
#define IDC_BUTTON_EDIT_ITEM 1004
#define IDC_BUTTON_FIND_ITEM 1005
#define IDC_BUTTON_SAVE 1006
#define IDC_TABLE 1007
#define IDC_BUTTON_CLEAR 1008

#define BUTTONS_WIDTH 140
#define BUTTONS_HEIGHT 30
#define TABLE_OFFSET_X 165
#define TABLE_COL_NUMBER 5

#define IDC_ITEMDIALOG_EDIT_0 1051
#define IDC_ITEMDIALOG_EDIT_1 1052
#define IDC_ITEMDIALOG_EDIT_2 1053
#define IDC_ITEMDIALOG_EDIT_3 1054
#define IDC_ITEMDIALOG_EDIT_4 1055

#define IDC_ADDITEMDIALOG_BUTTON_ADD 1056
#define IDC_ITEMDIALOG_STATIC_TEXT_0 1057
#define IDC_ITEMDIALOG_STATIC_TEXT_1 1058
#define IDC_ITEMDIALOG_STATIC_TEXT_2 1059
#define IDC_ITEMDIALOG_STATIC_TEXT_3 1060
#define IDC_ITEMDIALOG_STATIC_TEXT_4 1061
#define IDC_EDITITEMDIALOG_BUTTON_EDIT 1062

#define IDC_FINDITEMDIALOG_EDIT 1100
#define IDC_FINDITEMDIALOG_BUTTON_0 1101
#define IDC_FINDITEMDIALOG_BUTTON_1 1102
#define IDC_FINDITEMDIALOG_BUTTON_2 1103
#define IDC_FINDITEMDIALOG_BUTTON_3 1104
#define IDC_FINDITEMDIALOG_BUTTON_4 1105

#define TEXT_LABEL_0 L"����� �����"
#define TEXT_LABEL_1 L"����� ������� ������"
#define TEXT_LABEL_2 L"ϲ� ��������"
#define TEXT_LABEL_3 L"������ ���� ����������"
#define TEXT_LABEL_4 L"����� ��������"

#define FIND_LABEL_0 L"����� �� ������ ������"
#define FIND_LABEL_1 L"����� �� ������� ������� ������"
#define FIND_LABEL_2 L"����� �� ϲ�-��"
#define FIND_LABEL_3 L"����� �� �������"
#define FIND_LABEL_4 L"����� �� ������� ��������"

#define MAX_STR_LEN_COL_0 40
#define MAX_STR_LEN_COL_1 40
#define MAX_STR_LEN_COL_2 40
#define MAX_STR_LEN_COL_3 40
#define MAX_STR_LEN_COL_4 40
const int MAX_STR_LEN_COL[TABLE_COL_NUMBER] = { MAX_STR_LEN_COL_0 , MAX_STR_LEN_COL_1,
	MAX_STR_LEN_COL_2, MAX_STR_LEN_COL_3, MAX_STR_LEN_COL_4 };

#define COL_NAME_0 L"�����"
#define COL_NAME_1 L"� ������� ������"
#define COL_NAME_2 L"ϲ�"
#define COL_NAME_3 L"������"
#define COL_NAME_4 L"�������"

#endif
