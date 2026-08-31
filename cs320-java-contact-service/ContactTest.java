import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

class ContactTest {

    @Test
    void testGetters() {
        Contact contact = new Contact("12315518", "Uri", "Naor", "0534567890", "Awesome St 47");
        assertEquals("12315518", contact.getContactId());
        assertEquals("Uri", contact.getFirstName());
        assertEquals("Naor", contact.getLastName());
        assertEquals("0534567890", contact.getPhone());
        assertEquals("Awesome St 47", contact.getAddress());
    }

    @Test
    void testConstructorInvalidId() {
        // null id
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            new Contact(null, "Uri", "Naor", "0534567890", "Awesome St 47");
        });
        // id is too long
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            new Contact("12315518901", "Uri", "Naor", "0534567890", "Awesome St 47");
        });
    }

    @Test
    void setFirstName() {
        Contact contact = new Contact("12315518", "Uri", "Naor", "0534567890", "Awesome St 47");
        assertEquals("Uri", contact.getFirstName());
        contact.setFirstName("Mark");
        assertEquals("Mark", contact.getFirstName());

        Assertions.assertThrows(IllegalArgumentException.class, () -> contact.setFirstName(null));
        Assertions.assertThrows(IllegalArgumentException.class, () -> contact.setFirstName("LongAssFirstName"));
    }

    @Test
    void setLastName() {
        Contact contact = new Contact("12315518", "Uri", "Naor", "0534567890", "Awesome St 47");
        assertEquals("Naor", contact.getLastName());
        contact.setLastName("Markstein");
        assertEquals("Markstein", contact.getLastName());

        Assertions.assertThrows(IllegalArgumentException.class, () -> contact.setLastName(null));
        Assertions.assertThrows(IllegalArgumentException.class, () -> contact.setLastName("LongAssLastName"));
    }

    @Test
    void setPhone() {
        Contact contact = new Contact("12315518", "Uri", "Naor", "0534567890", "Awesome St 47");
        assertEquals("0534567890", contact.getPhone());
        contact.setPhone("0987654321");
        assertEquals("0987654321", contact.getPhone());

        Assertions.assertThrows(IllegalArgumentException.class, () -> contact.setPhone("123")); // too short
        Assertions.assertThrows(IllegalArgumentException.class, () -> contact.setPhone("12345678901")); // too longa
        Assertions.assertThrows(IllegalArgumentException.class, () -> contact.setPhone("abc4567890")); // not a number
        Assertions.assertThrows(IllegalArgumentException.class, () -> contact.setPhone("123-567890")); // non digit char
        Assertions.assertThrows(IllegalArgumentException.class, () -> contact.setPhone(null));
    }

    @Test
    void setAddress() {
        Contact contact = new Contact("12315518", "Uri", "Naor", "0534567890", "Awesome St 47");
        assertEquals("Awesome St 47", contact.getAddress());
        contact.setAddress("No Way 15");
        assertEquals("No Way 15", contact.getAddress());

        Assertions.assertThrows(IllegalArgumentException.class, () -> contact.setAddress(null));
        Assertions.assertThrows(IllegalArgumentException.class, () -> contact.setAddress("This address is definitely longer than what is allowed for sure"));
    }
}
