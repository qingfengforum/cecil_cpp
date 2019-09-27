#ifndef COPY_CONTROL_EXAMPLE_H_
#define COPY_CONTROL_EXAMPLE_H_

class Message {
    friend class Folder;
public:
    // folders is implicitly initialized to the empty set
    explicit Message(const std::string &str=""):
        contents(str){}
    // copy control to manage pointers to this message
    Message(const Message&); // copy constructor
    Message &operator=(const Message&); // copy-assignment operator
    ~Message(); // destructor

    // add/remove this Message from the specified Folder's set of messages
    void save(Folder&);
    void remove(Folder&);
    void swap(Message &lhs, Message &rhs);
private:
    std::string contents; //actual message text
    std::set<Folder*> folders; //Folders that have this message

    // utility functions used by copy construtor, assignment, destructor
    // add this message to the Folders that point to the parameter
    void add_to_folders(const Message& );
    // remove this message from every Folder in folders
    void remove_from_folders();
};


Message::Message(const Message &m) : 
        contents(m.contents), folders(m.folders) // set also can directly initialized?
{
    add_to_folders(m);
}
Message::~Message()
{
    remove_from_folders();
}

Message &Message::operator=(const Message &rhs)
{
    // handle self-assignment by removing pointers before inserting them
    remove_from_folders(); // update existing folders
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_folders(rhs); // add this message to those folders

    return *this;


}

void Message::swap(Message &lhs, Message &rhs)
{
    // remove
    for (auto f : lhs)
    {
        f->remMsg(&lhs);
    }
    for (auto f : rhs)
    {
        f->remMsg(&rhs);
    }

    swap(lhs.content, rhs.content); // use swap(set&, set&)
    swap(lhs.folders, rhs.folders); // use swap(string&, string&)

    for (auto f : lhs)
    {
        lhs->addMsg(&lhs);
    }
    for (auto f : rhs)
    {
        rhs->addMsg(&rhs);
    }


}


void Message::save(Folder& f)
{
    // this message belong to the folder f (message --> folder)
    folders.insert(&f);
    // f include the message this. (folder --> message)
    f.addMsg(this);
}

void Message::remove(Folder& f)
{
    // (message -/-> folder)
    folders.erase(&f);
    // (folder -/-> message)
    f.remMsg(this);
}


void Message::add_to_folders(const Message& m)
{
    for (auto f: m.folders)
    {
        f.addMsg(this);
    }
}

void Message::remove_from_folders()
{
    for (auto f:folders)
    {
        f.remMsg(this);
    }
}

#endif