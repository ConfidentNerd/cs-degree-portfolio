public class Contact {
    private final String contactId;
    private String firstName;
    private String lastName;
    private String phone;
    private String address;

    public Contact(String contactId, String firstName, String lastName, String phone, String address) {
        if (contactId == null || contactId.length() > 10) {
            throw new IllegalArgumentException("contactId can't be null or longer than 10 characters");
        }
        this.contactId = contactId;

        setFirstName(firstName);
        setLastName(lastName);
        setPhone(phone);
        setAddress(address);
    }

    //getters
    public String getContactId() {
        return contactId;
    }

    public String getFirstName() {
        return firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public String getPhone() {
        return phone;
    }

    public String getAddress() {
        return address;
    }

    //setters
    public final void setFirstName(String firstName) {
        if (firstName == null || firstName.length() > 10) {
            throw new IllegalArgumentException("firstName can't be null or longer than 10 characters");
        }
        this.firstName = firstName;
    }

    public final void setLastName(String lastName) {
        if (lastName == null || lastName.length() > 10) {
            throw new IllegalArgumentException("lastName can't be null or longer than 10 characters");
        }
        this.lastName = lastName;
    }

    public final void setPhone(String phone) {
        if (phone == null || phone.length() != 10) {
            throw new IllegalArgumentException("phone can't be null and must be 10 characters");
        }

        for (char ch : phone.toCharArray()) {
            if (ch < '0' || ch > '9') {
                throw new IllegalArgumentException(("a phone number can only contain numbers"));
            }
        }

        this.phone = phone;
    }

    public final void setAddress(String address) {
        if (address == null || address.length() > 30) {
            throw new IllegalArgumentException("address can't be null or longer than 30 characters");
        }
        this.address = address;
    }
}