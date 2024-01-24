import pygame
import math

inner_ring, outer_ring = pygame.sprite.Sprite, pygame.sprite.Sprite
inner_ring.rect, outer_ring.rect = pygame.Rect, pygame.Rect


def dotProduct(direction: int, line: tuple):
    # takes direction and a line coords (edge to centre), finds the angle of the line
    # todo: store the lines for the rectangle sides. assign them to each side?
    return


class Car(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()

        self.x,self.y = 150, 200
        self.v = 0
        self.a = 0
        self.vmax = 10 # magnitude
        self.direction = 0 # used for sprite drawing and direction

        self.image = pygame.image.load("direction.png")
        self.rect = self.image.get_rect()
        self.rect.x = self.x
        self.rect.y = self.y

    def update(self):
        # front arrow keys change vy
        # side arrow keys change vx

        # sets acceleration
        if pygame.key.get_pressed()[pygame.K_w]:
            self.a = -0.2
        elif pygame.key.get_pressed()[pygame.K_s]:
            self.a = 0.2
        else:
            self.a =0
        # if pygame.key.get_pressed()[pygame.K_a]:
        #     self.ax = -0.2
        # elif pygame.key.get_pressed()[pygame.K_d]:
        #     self.ax = 0.2
        # else:
        #     self.ax = 0

        # adds acceleration to velocity.
        # range: [-vmax, vmax]
        self.v = max(min(self.v + self.a, self.vmax), -self.vmax)
        #self.vy = max(min(self.vy + self.ay, self.vmax), -self.vmax)
        if self.a == 0:
            self.v += (0-self.v)/50
        # if self.ay == 0:
        #     self.vy += (0-self.vy)/50

        # sets direction.
        # uses radians
        if pygame.key.get_pressed()[pygame.K_d]:
            self.direction += math.pi/50

            # self.image = pygame.transform.scale(
            #     pygame.transform.rotate(self.image, -(math.pi/50 * (180/math.pi))),
            #     [10, 50]
            # )  # the sprite doesnt rotate properly

        elif pygame.key.get_pressed()[pygame.K_a]:
            self.direction -= math.pi / 50

            # self.image = pygame.transform.scale(
            #     pygame.transform.rotate(self.image, (math.pi / 50 * (180 / math.pi))),
            #     [10, 50]
            # )  # the sprite doesnt rotate properly



        # handles collisions



        # print(int(inner_ring.right))
        # if (self.rect.left < inner_ring.rect.right or self.rect.left < outer_ring.rect.right) and self.vx <0:
        #     self.vx = 0
        # if (self.isCollidingDirectional(inner_ring.rect.left, self.rect.right) or self.isCollidingDirectional(outer_ring.rect.left, self.rect.right)) and self.vx >0:
        #     self.vx = 0
        # if (self.isCollidingDirectional(self.rect.top, inner_ring.rect.bottom) or self.isCollidingDirectional(self.rect.top, outer_ring.rect.bottom)) and self.vy <0:
        #     self.vy = 0
        # if (self.isCollidingDirectional(inner_ring.rect.top, self.rect.bottom) or self.isCollidingDirectional(outer_ring.rect.top, self.rect.bottom)) and self.vy >0:
        #     self.vy = 0
        self.rect.x += self.v * math.cos(self.direction)
        self.rect.y += self.v * math.sin(self.direction)
    
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


def drawRectDebug(shape):
    shape.rect = pygame.draw.rect(window, (255, 255, 255), (200, 200, 1520, 680), 5, 100)

    shape_left = [shape.rect.left, shape.rect.center[1]]
    shape_left_rr = (shape.rect.bottomleft[1] - shape.rect.topleft[1]) / math.sqrt((shape.rect.bottomleft[0] - shape.rect.topleft[0])**2 + (shape.rect.bottomleft[1] - shape.rect.topleft[1])**2)

    shape_right = [shape.rect.right, shape.rect.center[1]]
    shape_right_rr = (shape.rect.bottomright[1] - shape.rect.topright[1]) / math.sqrt(
        (((shape.rect.bottomright[0] - shape.rect.topright[0]) ** 2) + ((shape.rect.bottomright[1] - shape.rect.topright[1]) ** 2)))


    shape_top = [shape.rect.center[0], shape.rect.top]
    shape_top_rr = (shape.rect.topleft[1] - shape.rect.topright[1]) / math.sqrt(
        ((shape.rect.topleft[0] - shape.rect.topright[0]) ** 2 + (shape.rect.topleft[1] - shape.rect.topright[1]) ** 2))

    shape_bottom = [shape.rect.center[0], shape.rect.bottom]
    shape_bottom_rr = (shape.rect.bottomright[1] - shape.rect.bottomleft[1]) / math.sqrt(
        ((shape.rect.bottomright[0] - shape.rect.bottomleft[0]) ** 2 + (shape.rect.bottomright[1] - shape.rect.bottomleft[1]) ** 2))



    pygame.draw.circle(window, (255, 0, 0), shape.rect.center, 10) # centre

    pygame.draw.circle(window, (255, 0, 0), shape_left, 10) # left
    pygame.draw.line(window, (255, 0, 0), shape_left, (shape_left[0]-(50*math.asin(shape_left_rr)), shape_left[1]+(50*math.acos(shape_left_rr))), 5)


    pygame.draw.circle(window, (255, 0, 0), shape_right, 10) # right
    pygame.draw.line(window, (255, 0, 0), shape_right,
                     (shape_right[0] + (50 * math.asin(shape_right_rr)), shape_right[1] + (50 * math.acos(shape_right_rr))),
                     5)

    pygame.draw.circle(window, (255, 0, 0), shape_top, 10) # top
    pygame.draw.line(window, (255, 0, 0), shape_top,
                     (shape_top[0] + (50 * math.asin(shape_top_rr)), shape_top[1] - (50 * math.acos(shape_top_rr))),
                     5)

    pygame.draw.circle(window, (255, 0, 0), shape_bottom, 10) # bottom
    pygame.draw.line(window, (255, 0, 0), shape_bottom,
                     (shape_bottom[0] + (50 * math.asin(shape_bottom_rr)), shape_bottom[1] + (50 * math.acos(shape_bottom_rr))),
                     5)




if __name__ == "__main__":
    pygame.init()
    window = pygame.display.set_mode([1920, 1080])
    clock = pygame.time.Clock()

    car = Car()
    carGroup = pygame.sprite.Group()
    carGroup.add(car)
    radius = 50

    while True:
        if pygame.key.get_pressed()[pygame.K_ESCAPE]:
            break
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                break

        # our ring
        drawRectDebug(inner_ring)
        #outer_ring.rect = pygame.draw.rect(window, (255, 255, 255), (0, 0, 1920, 1080), 5, 100)

        # carGroup.update()
        # carGroup.draw(window)
        #
        # # #direction
        # arrow = pygame.draw.line(window, (255, 0, 0), car.rect.center, (
        #         car.rect.center[0]-(radius * math.cos(car.direction)),
        #     car.rect.center[1] - (radius * math.sin(car.direction))
        # ), 5)



        pygame.display.flip()
        window.fill((0,0,0))
        clock.tick(60)

