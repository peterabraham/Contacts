#ifndef CONTACTDIALOG_H
#define CONTACTDIALOG_H

#include <QDialog>
#include "Contact.h"
#include "ContactsManager.h"

namespace Ui {
class ContactDialog;
}

enum class DialogMode {Create, Edit, View};

class ContactDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ContactDialog(QWidget *parent = nullptr);
    ~ContactDialog();

    void init();
    void setContactsMgr(ContactsManager* mgr) { m_contactsMgr = mgr; }
    void setContact(const Contact& contact)   { m_contact = contact; }
    void setMode(const DialogMode mode)       { m_dialogMode = mode; }

private:
    bool validate();

private slots:
    void on_createButton_clicked();
    //void on_cancelButton_clicked();

private:
    Ui::ContactDialog* ui;
    ContactsManager*   m_contactsMgr = nullptr;
    Contact            m_contact;
    DialogMode         m_dialogMode;
};

#endif // CONTACTDIALOG_H
