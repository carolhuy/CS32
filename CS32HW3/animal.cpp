//destructor order
//1. run through body of destructor 
//2. destruct member variables as needed 
//3. destruct base class if needed 

//animal (base class, abstract) 
class Animal {
public:
	//functions of animal 

	//Animal constructor 
	Animal(string nameAnimal) : m_name(nameAnimal){}

	//speak (pure virtual - always diff for each animal)
	//GCC - cannot define virtual function 
	virtual void speak() const = 0; 

	//name (not virtual, returns name stored in base class Animal) 
	string name() const {
		return m_name;
	}

	//moveAction (virtual - different for Duck) 
	virtual string moveAction() const {
		return "walk";
	}

	//pure virtual destructor 
	virtual ~Animal() = 0;

	//private member variable for Animal 
private:
	string m_name;
};

//pure virtual destructor(still needs to be defined)
Animal::~Animal() {}

//cat (derived class) 
class Cat : public Animal {
public:
	//cat constructor 
	Cat(string nameCat):Animal(nameCat){}

	//speak 
	virtual void speak() const {
		cout << "Meow";
	}

	//destructor 
	virtual ~Cat(){
		cout << "Destroying " << (*this).name()<<" the cat" << endl;
	}
};

//pig (derived class)
class Pig : public Animal {

public:
	//pig constructor 
	Pig(string namePig, int weight):Animal(namePig),m_weight(weight){}

	//Pigs under 160 pounds oink; pigs weighing at least 160 pounds grunt.
	virtual void speak() const {
		if (m_weight < 160) {
			cout << "Oink";
		}
		else {
			cout << "Grunt";
		}
	}

	virtual ~Pig() {
		cout << "Destroying " << (*this).name() << " the pig" << endl;
	}

private:
	int m_weight; 
};

//duck (derived class)
class Duck : public Animal {
public:
	//constructor for duck 
	Duck(string nameDuck):Animal(nameDuck) {}

	//speak
	virtual void speak() const {
		cout << "Quack";
	}

	//move
	virtual string moveAction() const {
		return "swim";
	}

	//destructor 
	virtual ~Duck() {
		cout << "Destroying " << (*this).name() << " the duck" <<endl;
	}
};