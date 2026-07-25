public class Main {
    public static void main(String[] args) {
        Persona persona1 = new Persona("Juan", 20);
        Persona persona2 = new Persona("Ana", 15);

        System.out.println(persona1.esMayorDeEdad()); // true
        System.out.println(persona2.esMayorDeEdad()); // false
    }
}
