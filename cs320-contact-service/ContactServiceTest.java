import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class ContactServiceTest {

    @Test
    void addContact() {
        ContactService contacts = new ContactService();
        contacts.addContact("1", "Uri", "Naor", "0534567890", "Awesome St 47");

        // same id
        Assertions.assertThrows(IllegalArgumentException.class, () -> contacts.addContact(
                "1", "Secret", "Spy", "0042006900", "In Your Closet"
                ));
    }

    @Test
    void deleteContact() {
        ContactService contacts = new ContactService();
        contacts.addContact("1", "Uri", "Naor", "0534567890", "Awesome St 47");
        contacts.deleteContact("1");
        
        // readding deleted
        Assertions.assertDoesNotThrow(() -> contacts.addContact("1", "Uri", "Naor", "0534567890", "Awesome St 47"));
    }

    @Test
    void updateFirstName() {
        ContactService contacts = new ContactService();
        contacts.addContact("1", "Uri", "Naor", "0534567890", "Awesome St 47");
        contacts.updateFirstName("1", "Mark");

        assertEquals("Mark", contacts.getContact("1").getFirstName());
        // can't update non-existing id
        Assertions.assertThrows(IllegalArgumentException.class, () -> contacts.updateFirstName("2", "Matt"));
    }

    @Test
    void updateLastName() {
        ContactService contacts = new ContactService();
        contacts.addContact("1", "Uri", "Naor", "0534567890", "Awesome St 47");
        contacts.updateLastName("1", "Markstein");

        assertEquals("Markstein", contacts.getContact("1").getLastName());
        Assertions.assertThrows(IllegalArgumentException.class, () -> contacts.updateLastName("2", "Mattstein")); // non-existing id
    }

    @Test
    void updatePhone() {
        ContactService contacts = new ContactService();
        contacts.addContact("1", "Uri", "Naor", "0534567890", "Awesome St 47");
        contacts.updatePhone("1", "0987654321");

        assertEquals("0987654321", contacts.getContact("1").getPhone());
        Assertions.assertThrows(IllegalArgumentException.class, () -> contacts.updatePhone("1", "123")); // too short
        Assertions.assertThrows(IllegalArgumentException.class, () -> contacts.updatePhone("2", "0987654321"));
    }

    @Test
    void updateAddress() {
        ContactService contacts = new ContactService();
        contacts.addContact("1", "Uri", "Naor", "0534567890", "Awesome St 47");
        contacts.updateAddress("1", "No Way 15");
        
        assertEquals("No Way 15", contacts.getContact("1").getAddress());
        Assertions.assertThrows(IllegalArgumentException.class, () -> contacts.updateAddress("2", "Nowhere 99"));
    }
}
