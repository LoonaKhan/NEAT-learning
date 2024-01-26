import pygame
import math



def dotProduct(direction: int, line: tuple):
    # takes direction and a line coords (edge to centre), finds the angle of the line
    return


class Car(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()

        self.x, self.y = 150, 200
        self.v = 0
        self.a = 0
        self.vmax = 10  # magnitude
        self.direction = 0  # used for sprite drawing and direction

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
            self.a = 0
        # if pygame.key.get_pressed()[pygame.K_a]:
        #     self.ax = -0.2
        # elif pygame.key.get_pressed()[pygame.K_d]:
        #     self.ax = 0.2
        # else:
        #     self.ax = 0

        # adds acceleration to velocity.
        # range: [-vmax, vmax]
        self.v = max(min(self.v + self.a, self.vmax), -self.vmax)
        # self.vy = max(min(self.vy + self.ay, self.vmax), -self.vmax)
        if self.a == 0:
            self.v += (0 - self.v) / 50
        # if self.ay == 0:
        #     self.vy += (0-self.vy)/50

        # sets direction.
        # uses radians
        if pygame.key.get_pressed()[pygame.K_d]:
            self.direction += math.pi / 50

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
        # todo: check if colliding with a given barrier, if so, determine the direction and dont let the car move unless the dot prodct between the 2 is <=0
        if (self.rect.x < 0 or
                self.rect.x > 1920 or
                pygame.sprite.collide_rect(self, inner_ring) or
                pygame.sprite.collide_rect(self, outer_ring)
        ): return True

def RectPoints(i_r, o_r):
    inner_shape_left = [i_r.left, i_r.center[1]]
    inner_shape_left_rr = (i_r.bottomleft[1] - i_r.topleft[1]) / math.sqrt(
        (i_r.bottomleft[0] - i_r.topleft[0]) ** 2 + (
                i_r.bottomleft[1] - i_r.topleft[1]) ** 2)

    inner_shape_right = [i_r.right, i_r.center[1]]
    inner_shape_right_rr = (i_r.bottomright[1] - i_r.topright[1]) / math.sqrt(
        (((i_r.bottomright[0] - i_r.topright[0]) ** 2) + (
                (i_r.bottomright[1] - i_r.topright[1]) ** 2)))

    inner_shape_top = [i_r.center[0], i_r.top]
    inner_shape_top_rr = (i_r.topleft[1] - i_r.topright[1]) / math.sqrt(
        ((i_r.topleft[0] - i_r.topright[0]) ** 2 + (
                i_r.topleft[1] - i_r.topright[1]) ** 2))

    inner_shape_bottom = [i_r.center[0], i_r.bottom]
    inner_shape_bottom_rr = (i_r.bottomright[1] - i_r.bottomleft[1]) / math.sqrt(
        ((i_r.bottomright[0] - i_r.bottomleft[0]) ** 2 + (
                i_r.bottomright[1] - i_r.bottomleft[1]) ** 2))

    outer_shape_left = [o_r.left, o_r.center[1]]
    outer_shape_left_rr = (o_r.bottomleft[1] - o_r.topleft[1]) / math.sqrt(
        (o_r.bottomleft[0] - o_r.topleft[0]) ** 2 + (
                o_r.bottomleft[1] - o_r.topleft[1]) ** 2)

    outer_shape_right = [o_r.right, o_r.center[1]]
    outer_shape_right_rr = (o_r.bottomright[1] - o_r.topright[1]) / math.sqrt(
        (((o_r.bottomright[0] - o_r.topright[0]) ** 2) + (
                (o_r.bottomright[1] - o_r.topright[1]) ** 2)))

    outer_shape_top = [o_r.center[0], o_r.top]
    outer_shape_top_rr = (o_r.topleft[1] - o_r.topright[1]) / math.sqrt(
        ((o_r.topleft[0] - o_r.topright[0]) ** 2 + (
                o_r.topleft[1] - o_r.topright[1]) ** 2))

    outer_shape_bottom = [o_r.center[0], o_r.bottom]
    outer_shape_bottom_rr = (o_r.bottomright[1] - o_r.bottomleft[1]) / math.sqrt(
        ((o_r.bottomright[0] - o_r.bottomleft[0]) ** 2 + (
                o_r.bottomright[1] - o_r.bottomleft[1]) ** 2))

    return [{"left": inner_shape_left, "left_rr": inner_shape_left_rr, "right":inner_shape_right, "right_rr": inner_shape_right_rr, "top": inner_shape_top, "top_rr": inner_shape_top_rr, "bottom": inner_shape_bottom, "bottom_rr": inner_shape_bottom_rr}, \
{"left": outer_shape_left, "left_rr": outer_shape_left_rr, "right":outer_shape_right, "right_rr": outer_shape_right_rr, "top": outer_shape_top, "top_rr": outer_shape_top_rr, "bottom": outer_shape_bottom, "bottom_rr": outer_shape_bottom_rr}]

def RectPointsDebug(rings):


    pygame.draw.circle(window, (255, 0, 0), rings[0]["rect"].center, 10)  # centre

    pygame.draw.circle(window, (255, 0, 0), rings[0]["points"]["left"], 10)  # left
    pygame.draw.line(window, (255, 0, 0), rings[0]["points"]["left"], (
    rings[0]["points"]["left"][0] - (50 * math.asin(rings[0]["points"]["left_rr"])),
    rings[0]["points"]["left"][1] + (50 * math.acos(rings[0]["points"]["left_rr"]))), 5)

    pygame.draw.circle(window, (255, 0, 0), rings[0]["points"]["right"], 10)  # right
    pygame.draw.line(window, (255, 0, 0), rings[0]["points"]["right"],
                     (rings[0]["points"]["right"][0] + (50 * math.asin(rings[0]["points"]["right_rr"])),
                      rings[0]["points"]["right"][1] + (50 * math.acos(rings[0]["points"]["right_rr"]))),
                     5)

    pygame.draw.circle(window, (255, 0, 0), rings[0]["points"]["top"], 10)  # top
    pygame.draw.line(window, (255, 0, 0), rings[0]["points"]["top"],
                     (rings[0]["points"]["top"][0] + (50 * math.asin(rings[0]["points"]["top_rr"])),
                      rings[0]["points"]["top"][1] - (50 * math.acos(rings[0]["points"]["top_rr"]))),
                     5)

    pygame.draw.circle(window, (255, 0, 0), rings[0]["points"]["bottom"], 10)  # bottom
    pygame.draw.line(window, (255, 0, 0), rings[0]["points"]["bottom"],
                     (rings[0]["points"]["bottom"][0] + (50 * math.asin(rings[0]["points"]["bottom_rr"])),
                      rings[0]["points"]["bottom"][1] + (50 * math.acos(rings[0]["points"]["bottom_rr"]))),
                     5)

    # OUTER RING
    pygame.draw.circle(window, (255, 0, 0), rings[1]["rect"].center, 10)  # centre

    pygame.draw.circle(window, (255, 0, 0), rings[1]["points"]["left"], 10)  # left
    pygame.draw.line(window, (255, 0, 0),  rings[1]["points"]["left"], (
        rings[1]["points"]["left"][0] + (50 * math.asin( rings[1]["points"]["left_rr"])),
        rings[1]["points"]["left"][1] + (50 * math.acos( rings[1]["points"]["left_rr"]))), 5)

    pygame.draw.circle(window, (255, 0, 0), rings[1]["points"]["right"], 10)  # right
    pygame.draw.line(window, (255, 0, 0), rings[1]["points"]["right"],
                     (rings[1]["points"]["right"][0] - (50 * math.asin(rings[1]["points"]["right_rr"])),
                      rings[1]["points"]["right"][1] + (50 * math.acos(rings[1]["points"]["right_rr"]))),
                     5)

    pygame.draw.circle(window, (255, 0, 0), rings[1]["points"]["top"], 10)  # top
    pygame.draw.line(window, (255, 0, 0), rings[1]["points"]["top"],
                     (rings[1]["points"]["top"][0] + (50 * math.asin(rings[1]["points"]["top_rr"])),
                      rings[1]["points"]["top"][1] + (50 * math.acos(rings[1]["points"]["top_rr"]))),
                     5)

    pygame.draw.circle(window, (255, 0, 0), rings[1]["points"]["bottom"], 10)  # bottom
    pygame.draw.line(window, (255, 0, 0), rings[1]["points"]["bottom"],
                     (rings[1]["points"]["bottom"][0] + (50 * math.asin(rings[1]["points"]["bottom_rr"])),
                      rings[1]["points"]["bottom"][1] - (50 * math.acos(rings[1]["points"]["bottom_rr"]))),
                     5)


if __name__ == "__main__":
    pygame.init()
    window = pygame.display.set_mode([1920, 1080])
    clock = pygame.time.Clock()

    car = Car()
    carGroup = pygame.sprite.Group()
    carGroup.add(car)
    radius = 50

    inner_ring, outer_ring = pygame.draw.rect(window, (255, 255, 255), (200, 200, 1520, 680), 5, 100), \
            pygame.draw.rect(window, (255, 255, 255), (0, 0, 1920, 1080), 5, 100)
    rings = [
        {"rect": inner_ring, "points": RectPoints(inner_ring, outer_ring)[0]},
        {"rect": outer_ring, "points": RectPoints(inner_ring, outer_ring)[1]}
    ]


    while True:
        if pygame.key.get_pressed()[pygame.K_ESCAPE]:
            break
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                break

        # our rings
        rings[0]["rect"], rings[1]["rect"] = pygame.draw.rect(window, (255, 255, 255), (200, 200, 1520, 680), 5, 100), \
            pygame.draw.rect(window, (255, 255, 255), (0, 0, 1920, 1080), 5, 100)


        RectPointsDebug(rings)

        carGroup.update()
        carGroup.draw(window)

        # #direction
        arrow = pygame.draw.line(window, (255, 0, 0), car.rect.center, (
                car.rect.center[0]-(radius * math.cos(car.direction)),
            car.rect.center[1] - (radius * math.sin(car.direction))
        ), 5)

        pygame.display.flip()
        window.fill((0, 0, 0))
        clock.tick(60)
