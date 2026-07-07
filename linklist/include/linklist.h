#ifndef LINKLIST_H
#define LINKLIST_H

#include "student.h"

#define SUCCESS 1
#define FAILURE 0

typedef struct Node
{
  student data;
  struct Node *next;
} Node;

typedef struct LinkList
{
  Node *head;
  Node *tail;
  int size;
} LinkList;

/// @brief Tao mot node moi voi du lieu sinh vien cho truoc
/// @param data Du lieu sinh vien muon them vao node
/// @return Con tro den node moi duoc tao, hoac NULL neu loi
Node *newnode(student data);

/// @brief Khoi tao danh sach lien ket rong
/// @param list Con tro den danh sach lien ket can khoi tao
void khoi_tao(LinkList *list);

/// @brief Xoa toan bo cac node va giai phong bo nho cua danh sach
/// @param list Con tro den danh sach lien ket can xoa
void xoa_list(LinkList *list);

/// @brief Them mot node chua du lieu sinh vien vao dau danh sach
/// @param list Con tro den danh sach lien ket
/// @param data Du lieu sinh vien muon them
/// @return SUCCESS neu thanh cong, FAILURE neu loi
int themdau(LinkList *list, student data);

/// @brief Them mot node chua du lieu sinh vien vao cuoi danh sach
/// @param list Con tro den danh sach lien ket
/// @param data Du lieu sinh vien muon them
/// @return SUCCESS neu thanh cong, FAILURE neu loi
int themcuoi(LinkList *list, student data);

/// @brief Them mot node chua du lieu sinh vien vao vi tri bat ky trong danh sach
/// @param list Con tro den danh sach lien ket
/// @param data Du lieu sinh vien muon them
/// @param vt Vi tri can them (0 den size)
/// @return SUCCESS neu thanh cong, FAILURE neu loi
int themgiua(LinkList *list, student data, int vt);

/// @brief Xoa node o dau danh sach
/// @param list Con tro den danh sach lien ket
/// @return SUCCESS neu thanh cong, FAILURE neu loi
int xoadau(LinkList *list);

/// @brief Xoa node o cuoi danh sach
/// @param list Con tro den danh sach lien ket
/// @return SUCCESS neu thanh cong, FAILURE neu loi
int xoacuoi(LinkList *list);

/// @brief Xoa node o vi tri bat ky trong danh sach
/// @param list Con tro den danh sach lien ket
/// @param vt Vi tri can xoa (0 den size-1)
/// @return SUCCESS neu thanh cong, FAILURE neu loi
int xoagiua(LinkList *list, int vt);

typedef void (*studentCB)(student s);
/// @brief Duyet qua tat ca sinh vien va thuc thi ham callback cho tung sinh vien
/// @param list Con tro den danh sach lien ket
/// @param cb Con tro ham callback xu ly tung sinh vien
void all(LinkList *list, studentCB cb);

typedef int (*searchCB)(student s);
/// @brief Tim kiem sinh vien dau tien thoa man dieu kien trong ham callback
/// @param list Con tro den danh sach lien ket
/// @param cb Con tro ham callback kiem tra dieu kien sinh vien
/// @return Node tim thay dau tien, hoac NULL neu khong tim thay
Node *search(LinkList *list, searchCB cb);

typedef int (*arrangeCB)(student s1, student s2);
/// @brief Sap xep danh sach lien ket theo tieu chi trong ham so sanh callback
/// @param list Con tro den danh sach lien ket
/// @param cb Con tro ham callback dung de so sanh hai sinh vien
void arrange(LinkList *list, arrangeCB cb);

// void capnhat(Node *head, student data, int vt);
// void xemnode (Node * head, int vt);
// void xemtoanbo(Node *head);
/// @brief Giai phong toan bo bo nho cua cac node bat dau tu con tro head
/// @param head Con tro den con tro dau cua danh sach
void freeall(Node **head);

/// @brief Dem so luong node trong danh sach bat dau tu node head
/// @param head Con tro den node dau
/// @return So luong node dem duoc
int demnode(Node *head);
#endif