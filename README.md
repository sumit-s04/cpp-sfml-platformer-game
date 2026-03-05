# cpp-sfml-platformer-game
A 2D platformer game built in C++ using the SFML graphics library. Features custom movement physics, collision detection, enemies, and collectibles.

# How to Run the Game

This project was built on VSCode using **C++ and the SFML graphics library**.
To run the game on your own system, you will need to update the asset file paths used by the project.

The current asset paths point to the developer's local directory. These paths must be updated to match the location of the files on your machine.

---

## Step 1: Clone the Repository

```bash
git clone https://github.com/sumit-s04/cpp-sfml-platformer-game.git

cd cpp-sfml-platformer-game
```

---

## Step 2: Locate the Asset Paths

The game loads textures using `loadFromFile()` calls inside **Functions.h** and **Game.h**.

These currently look like this:

```cpp
blockTexture.loadFromFile("/home/sumit/Sumit/Project/br(1).jpg");
```

You will need to change the directory path so it matches where the asset files are located on your computer.

For example:

```cpp
blockTexture.loadFromFile("assets/br(1).jpg");
```

---

## Step 3: Quickly Find All Paths

The easiest way to update these paths is to **search for `loadFromFile` in the project code**.

Most editors allow this with:

```
Ctrl + F
```

Search for:

```
loadFromFile
```

Update the directory portion of each path so it points to the correct location of the image files on your system.

These occur in:

* `Functions.h`
* `Game.h`

---

## Step 4: Update the Font Path

There is also a font file path defined in **Functions.h (line 11)**.
Update this path the same way to point to the correct font file location on your system.

---

## Step 5: Compile and Run

After updating the paths, compile and run the program with SFML installed.

Example:

```
g++ main.cpp -o sfml_example -I/usr/local/include -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system

./sfml_example
```

