import java.util.HashMap;

public class ContactService {
    private final HashMap<String, Contact> contacts;

    public ContactService() {
        contacts = new HashMap<>();
    }

    public void addContact(String contactId, String firstName, String lastName, String phone, String address) {
        if (contacts.containsKey(contactId)) {
            throw new IllegalArgumentException("contactId must be unique");
        }

        Contact newContact = new Contact(contactId, firstName, lastName, phone, address);

        contacts.put(contactId, newContact);
    }

    public Contact getContact(String contactId) {
        return contacts.get(contactId);
    }

    public void deleteContact(String contactId) {
        contacts.remove(contactId);
    }

    public void updateFirstName(String contactId, String firstName) {
        Contact foundContact = contacts.get(contactId);

        if (foundContact == null) {
            throw new IllegalArgumentException("contactId not found");
        }

        foundContact.setFirstName(firstName);
    }

    public void updateLastName(String contactId, String lastName) {
        Contact foundContact = contacts.get(contactId);

        if (foundContact == null) {
            throw new IllegalArgumentException("contactId not found");
        }

        foundContact.setLastName(lastName);
    }

    public void updatePhone(String contactId, String phone) {
        Contact foundContact = contacts.get(contactId);

        if (foundContact == null) {
            throw new IllegalArgumentException("contactId not found");
        }

        foundContact.setPhone(phone);
    }

    public void updateAddress(String contactId, String address) {
        Contact foundContact = contacts.get(contactId);

        if (foundContact == null) {
            throw new IllegalArgumentException("contactId not found");
        }

        foundContact.setAddress(address);
    }
}
