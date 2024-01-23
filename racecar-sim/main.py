import pygame
import math

inner_ring, outer_ring = pygame.sprite.Sprite, pygame.sprite.Sprite
inner_ring.rect, outer_ring.rect = pygame.Rect, pygame.Rect


class Car(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()

        self.x,self.y = 960, 540
        self.vx, self.vy = 0, 0
        self.ax, self.ay = 0, 0
        self.vmax = 10 # magnitude
        #self.direction = 0 # used for sprite drawing and direction

        self.image = pygame.image.load("direction.png")
        self.rect = self.image.get_rect()
        self.rect.x = self.x
        self.rect.y = self.y

    def update(self):
        # front arrow keys change vy
        # side arrow keys change vx

        # sets acceleration
        if pygame.key.get_pressed()[pygame.K_w]:
            self.ay = -0.2
        elif pygame.key.get_pressed()[pygame.K_s]:
            self.ay = 0.2
        else:
            self.ay =0
        if pygame.key.get_pressed()[pygame.K_a]:
            self.ax = -0.2
        elif pygame.key.get_pressed()[pygame.K_d]:
            self.ax = 0.2
        else:
            self.ax = 0

        # adds acceleration to velocity.
        # range: [-vmax, vmax]
        self.vx = max(min(self.vx + self.ax, self.vmax), -self.vmax)
        self.vy = max(min(self.vy + self.ay, self.vmax), -self.vmax)
        if self.ax == 0:
            self.vx += (0-self.vx)/50
        if self.ay == 0:
            self.vy += (0-self.vy)/50

        # sets direction.
        # uses radians
        # if pygame.key.get_pressed()[pygame.K_d]:
        #     self.direction += math.pi/50
        #
        #     self.image = pygame.transform.scale(
        #         pygame.transform.rotate(self.image, -(math.pi/50 * (180/math.pi))),
        #         [10, 50]
        #     )  # the sprite doesnt rotate properly
        #
        # elif pygame.key.get_pressed()[pygame.K_a]:
        #     self.direction -= math.pi / 50
        #
        #     self.image = pygame.transform.scale(
        #         pygame.transform.rotate(self.image, (math.pi / 50 * (180 / math.pi))),
        #         [10, 50]
        #     )  # the sprite doesnt rotate properly



        # handles collisions
        # print(int(inner_ring.right))
        if (self.isCollidingDirectional(self.rect.left, inner_ring.rect.right) or self.isCollidingDirectional(self.rect.left, outer_ring.rect.right)) and self.vx <0:
            self.vx = 0
        if (self.isCollidingDirectional(inner_ring.rect.left, self.rect.right) or self.isCollidingDirectional(outer_ring.rect.left, self.rect.right)) and self.vx >0:
            self.vx = 0
        if (self.isCollidingDirectional(self.rect.top, inner_ring.rect.bottom) or self.isCollidingDirectional(self.rect.top, outer_ring.rect.bottom)) and self.vy <0:
            self.vy = 0
        if (self.isCollidingDirectional(inner_ring.rect.top, self.rect.bottom) or self.isCollidingDirectional(outer_ring.rect.top, self.rect.bottom)) and self.vy >0:
            self.vy = 0
        self.rect.x += self.vx
        self.rect.y += self.vy
    
    def isColliding(self, inner_ring, outer_ring):
        # cannot go out of bounds or through barriers
        # return true if colliding with barriers
        if (self.rect.x <0 or
                self.rect.x > 1920 or
            pygame.sprite.collide_rect(self, inner_ring) or
            pygame.sprite.collide_rect(self, outer_ring)
        ): return True

    def isCollidingDirectional(self, left, right):
        return left < right



if __name__ == "__main__":
    pygame.init()
    window = pygame.display.set_mode([1920, 1080], pygame.FULLSCREEN)
    clock = pygame.time.Clock()

    car = Car()
    carGroup = pygame.sprite.Group()
    carGroup.add(car)
    radius = 50

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT or pygame.key.get_pressed()[pygame.K_ESCAPE]:
                break

                # our ring
                inner_ring.rect = pygame.draw.rect(window, (255, 255, 255), (200, 200, 1520, 680), 5, 100)
                outer_ring.rect = pygame.draw.rect(window, (255, 255, 255), (0, 0, 1920, 1080), 5, 100)

        carGroup.update()
        carGroup.draw(window)

        # #direction
        # arrow = pygame.draw.line(window, (255, 0, 0), car.rect.center, (
        #         car.rect.center[0]-(radius * math.cos(car.direction)),
        #     car.rect.center[1] - (radius * math.sin(car.direction))
        # ), 5)



        pygame.display.flip()
        window.fill((0,0,0))
        clock.tick(60)

