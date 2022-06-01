#include "MainDialog.h"
#include "ui_MainDialog.h"
#include "ContactDialog.h"
//#include "ui_contactdialog.h"
#include "ContactsManager.h"
#include "Contact.h"
#include <QStringList>
//#include <QDialog>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->buttonsLayout->addWidget(ui->createContactButton);
    ui->buttonsLayout->addWidget(ui->editContactButton);
    ui->buttonsLayout->addWidget(ui->deleteContactButton);
    ui->contactList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //this->setWindowTitle("Contacts");

    // Attaching String list model to the contacts list view
    m_contactModel = new QStringListModel(this);
    ui->contactList->setModel(m_contactModel);

    // setupUi() connects the slots by name invoking QMetaObject::connectSlotsByName()
    //connect(ui->createContactButton, SIGNAL(clicked()), this, SLOT(on_createContactButton_clicked()));
    //connect(ui->editContactButton, SIGNAL(clicked()), this, SLOT(on_editContactButton_clicked()));
    //connect(ui->deleteContactButton, SIGNAL(clicked()), this, SLOT(on_deleteContactButton_clicked()));
    //connect(ui->refreshButton, SIGNAL(clicked()), this, SLOT(on_refreshButton_clicked()));
    //connect(ui->searchButton, SIGNAL(textChanged()), this, SLOT(on_searchButton_clicked()));
    //connect(ui->contactList, SIGNAL(setCurrentIndex()), this, SLOT(on_contactSelected()));
    connect(ui->contactList, SIGNAL(clicked(QModelIndex)), this, SLOT(on_contactSelected(QModelIndex)));
    connect(ui->contactList, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_contactDoubleClicked(QModelIndex)));

    m_contactsMgr = new ContactsManager();
    m_contactsMgr->setGuiCallBack(std::bind(&Dialog::guiCallBack, this, std::placeholders::_1));

    m_contactsMgr->getAllContacts();
}

Dialog::~Dialog()
{
    delete ui;
    delete m_contactsMgr;
}

void Dialog::on_createContactButton_clicked()
{
    auto contactDlg = ContactDialog(this);
    contactDlg.setMode(DialogMode::Create);
    contactDlg.setContactsMgr(m_contactsMgr);
    contactDlg.init();
    contactDlg.exec();
}

void Dialog::on_refreshButton_clicked()
{
    ui->contactSearch->clear();
    m_contactsMgr->getAllContacts();
}

void Dialog::on_editContactButton_clicked()
{
    auto index = ui->contactList->currentIndex().row();
    auto contact = m_contactList[index];

    auto contactDlg = ContactDialog(this);
    contactDlg.setMode(DialogMode::Edit);
    contactDlg.setContact(contact);
    contactDlg.setContactsMgr(m_contactsMgr);
    contactDlg.init();
    contactDlg.exec();
}

void Dialog::on_deleteContactButton_clicked()
{
    auto index = ui->contactList->currentIndex().row();
    auto uuid  = m_contactList[index].contactid;
    m_contactsMgr->deleteContact(uuid);

    m_contactsMgr->getAllContacts();
}

void Dialog::on_searchButton_clicked()
{
    auto text = ui->contactSearch->text();
    m_contactsMgr->searchContact(text.toStdString());
}

void Dialog::on_contactSelected(const QModelIndex &selected)
{
    ui->deleteContactButton->setEnabled(true);
    ui->editContactButton->setEnabled(true);
}

void Dialog::on_contactDoubleClicked(const QModelIndex &selected)
{
    auto index = ui->contactList->currentIndex().row();
    auto contact = m_contactList[index];

    auto contactDlg = ContactDialog(this);
    contactDlg.setMode(DialogMode::View);
    contactDlg.setContact(contact);
    contactDlg.setContactsMgr(m_contactsMgr);
    contactDlg.init();
    contactDlg.exec();
}

void Dialog::guiCallBack(const std::vector<Contact>& contactList)
{
    m_contactList = contactList;

    QStringList list;
    for (auto& contact: m_contactList)
    {
        list << QString::fromStdString(contact.firstname + " " + contact.lastname);
    }
    m_contactModel->setStringList(list);

    ui->editContactButton->setEnabled(false);
    ui->deleteContactButton->setEnabled(false);
}
