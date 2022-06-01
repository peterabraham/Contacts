#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QStringListModel>
#include <vector>
#include <QItemSelection>
//#include "ContactsManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

// Forward declarations
class ContactsManager;
class Contact;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_createContactButton_clicked();
    void on_refreshButton_clicked();
    void on_editContactButton_clicked();
    void on_deleteContactButton_clicked();
    void on_searchButton_clicked();
    void on_contactSelected(const QModelIndex &selected);
    void on_contactDoubleClicked(const QModelIndex &selected);

private:
    void guiCallBack(const std::vector<Contact>& contactList);

private:
    Ui::Dialog *ui;
    QStringListModel *m_contactModel;
    ContactsManager* m_contactsMgr;
    std::vector<Contact> m_contactList;
};
#endif // DIALOG_H
