#include "ContactDialog.h"
#include "ui_contactdialog.h"
#include <QMessageBox>
#include <QIntValidator>

ContactDialog::ContactDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContactDialog)
{
    ui->setupUi(this);

    ui->phoneEdit->setValidator(new QIntValidator);
    //connect(ui->createButton, SIGNAL(clicked()), this, SLOT(on_createButton_clicked()));
    //connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(on_editContactButton_clicked()));
}

void ContactDialog::init()
{
    auto setUIFields = [this](){
        ui->firstNameEdit->setText(QString::fromUtf8(m_contact.firstname.c_str()));
        ui->lastNameEdit->setText(QString::fromUtf8(m_contact.lastname.c_str()));
        ui->phoneEdit->setText(QString::number(m_contact.phone));
        ui->emailEdit->setText(QString::fromUtf8(m_contact.email.c_str()));
    };

    auto enableUIFields = [this](bool flag) {
        ui->firstNameEdit->setEnabled(flag);
        ui->lastNameEdit->setEnabled(flag);
        ui->phoneEdit->setEnabled(flag);
        ui->emailEdit->setEnabled(flag);
    };

    if (m_dialogMode == DialogMode::Create)
    {
        this->setWindowTitle("Create New Contact");
        ui->createButton->setText("Create");
        ui->cancelButton->setText("Cancel");
    }
    else if (m_dialogMode == DialogMode::Edit)
    {
        this->setWindowTitle("Edit Contact");
        ui->createButton->setText("Apply");
        ui->cancelButton->setText("Cancel");
        enableUIFields(true);
        setUIFields();
    }
    else
    {
        this->setWindowTitle("View Contact");
        ui->createButton->setText("Edit");
        ui->cancelButton->setText("Close");
        setUIFields();
        enableUIFields(false);
    }
}

ContactDialog::~ContactDialog()
{
    delete ui;
}

bool ContactDialog::validate()
{
    if (ui->firstNameEdit->text().isEmpty() || ui->phoneEdit->text().isEmpty())
        return false;
    return true;
}

void ContactDialog::on_createButton_clicked()
{
    if (m_dialogMode == DialogMode::View)
    {
        m_dialogMode = DialogMode::Edit;
        init();
    }
    else if (validate())
    {
        auto contact = Contact();
        contact.firstname = ui->firstNameEdit->text().toStdString();
        contact.lastname = ui->lastNameEdit->text().toStdString();
        contact.phone = ui->phoneEdit->text().toLong();
        contact.email = ui->emailEdit->text().toStdString();
        if (m_dialogMode == DialogMode::Create)
        {
            m_contactsMgr->createContact(contact);
        }
        else
        {
            contact.contactid = m_contact.contactid;
            m_contactsMgr->editContact(contact);
        }

        m_contactsMgr->getAllContacts();
        accept();
    }
    else
    {
        QMessageBox::information(this, "Warning", "Failed to enter the mandatory field(s)");
    }
}

//void ContactDialog::on_cancelButton_clicked()
//{

//}
