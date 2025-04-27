#pragma once

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window.hpp>
#include <chrono>

class Engine {
public:
  void run() {
    hero.setTextureRect(animation_rectangle);

    while (window.isOpen()) {
      handle_events();
      update();
      draw();
    }
  }

private:
  void handle_events() {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
    }
  }

  void update() {
    dt = clock.restart();
    aimation_time += dt;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) {
      hero.move({-1 * dt.asSeconds() * speed, 0});
      animation_rectangle_cords.y = 64 * 3;
      is_pressed = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) {
      hero.move({1 * dt.asSeconds() * speed, 0});
      animation_rectangle_cords.y = 64;
      is_pressed = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) {
      hero.move({0, 1 * dt.asSeconds() * speed});
      animation_rectangle_cords.y = 64 * 2;
      is_pressed = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) {
      hero.move({0, -1 * dt.asSeconds() * speed});
      animation_rectangle_cords.y = 0;
      is_pressed = true;
    }

    if (is_pressed) {
      if (aimation_time >= animation_speed) {
        animation_rectangle_cords.x += texture_size.x;
        animation_rectangle_cords.x %= texture_size.x * 3;
        // 0 % 144 = 0
        // 48 % 144 = 48
        // 96 % 144 = 96
        // 144 % 144 = 0

        aimation_time = sf::Time::Zero;
      }
    }

    is_pressed = false;

    hero.setTextureRect({animation_rectangle_cords, texture_size});
  }

  void draw() {
    window.clear();
    window.draw(background_sprite);
    window.draw(hero);
    window.display();
  }

  sf::RenderWindow window{sf::VideoMode({2048, 1024}), "SFML works!"};
  sf::Clock clock;
  sf::Time dt;
  float speed{100};
  sf::Texture background_texture{"./background.png"};
  sf::Sprite background_sprite{background_texture};

  sf::Vector2i texture_size{48, 64};

  sf::Texture image{"./image.png"};
  sf::Sprite hero{image};
  sf::IntRect animation_rectangle{{0, 0}, texture_size};
  sf::Vector2i animation_rectangle_cords{0, 0};
  sf::Time animation_speed{std::chrono::milliseconds{100}};
  sf::Time aimation_time;
  bool is_pressed = false;
};