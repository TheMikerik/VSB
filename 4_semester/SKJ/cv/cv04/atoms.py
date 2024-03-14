import playground
import random


class Atom:
    def __init__(self, x, y, rad, color, speed_x, speed_y):
        self.x = x
        self.y = y
        self.rad = rad
        self.color = color
        self.speed_x = speed_x
        self.speed_y = speed_y
        pass

    def to_tuple(self):
        return (self.x, self.y, self.rad, self.color)
        pass

    def move(self, width, height):
        if self.x + self.speed_x < 0:
            self.speed_x = -self.speed_x
        if self.x + self.speed_x > width:
            self.speed_x = -self.speed_x
        if self.y + self.speed_y < 0:
            self.speed_y = -self.speed_y
        if self.y + self.speed_y > height:
            self.speed_y = -self.speed_y
        
        self.x += self.speed_x
        self.y += self.speed_y
        pass


class ExampleWorld(object):

    def __init__(self, size_x, size_y, count):
        self.width = size_x
        self.height = size_y
        self.count = count
        self.atomCount = 0;
        self.atoms = []

        while self.atomCount < self.count:
            self.random_atom()


    def random_atom(self):
        if self.atomCount >= self.count:
            print('Max atoms reached')
            return None
        else:
            self.atomCount += 1

            rand_x = random.randint(1, self.width - 1)
            rand_y = random.randint(1, self.height - 1)
            rand_rad = random.randint(5, 50)
            rand_color = random.choice(['blue', 'red', 'green', 'black', 'yellow'])
            rand_speed_x = random.randint(-200, 200)
            rand_speed_y = random.randint(-8, 8)

            new_atom = FallDownAtom(rand_x, rand_y, rand_rad, rand_color, rand_speed_x, rand_speed_y)
            self.atoms.append(new_atom)
        pass

    def tick(self):
        for atom in self.atoms:
            atom.move(self.width, self.height)

        return tuple(atom.to_tuple() for atom in self.atoms)

class FallDownAtom(Atom):
    g = 3.0
    damping = 0.8

    def move(self, width, height):
        if self.x + self.speed_x < 0:
            self.speed_x = -self.speed_x
        if self.x + self.speed_x > width:
            self.speed_x = -self.speed_x
        if self.y + self.speed_y < 0:
            self.speed_y = -self.speed_y
        if self.y + self.speed_y > height:
            self.speed_y = -self.speed_y

        if self.y <= height:
            self.speed_y *= self.damping
            self.speed_x *= self.damping

        

        self.x += self.speed_x
        # self.y += self.speed_y

        self.speed_y += self.g

        pass

if __name__ == '__main__':
    size_x, size_y = 700, 400
    count = 20

    world = ExampleWorld(size_x, size_y, count)
    playground.run((size_x, size_y), world)
