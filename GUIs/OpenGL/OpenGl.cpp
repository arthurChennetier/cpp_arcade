//
// OpenGl.cpp for OPENGL in /home/chauvin/Rendu-2017-Epitech/CPP/clone/cpp_arcade/GUIs/OpenGL
// 
// Made by chauvin
// Login   <chauvi_d>
// 
// Started on  Sun Apr  9 22:36:41 2017 chauvin
// Last update Sun Apr  9 22:55:23 2017 chauvin
//

#include "OpenGl.hpp"
#include "Font.hpp"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  static double lastTime = glfwGetTime();
  double currentTime = glfwGetTime();
  float deltaTime = float(currentTime - lastTime);
  OpenGl *pointer = (OpenGl*) glfwGetWindowUserPointer(window);

  (void)scancode;
  (void)mode;
  if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    pointer->set_DIR(Game::Command::UP);
  else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    pointer->set_DIR(Game::Command::ESCAPE);
  else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	  pointer->set_DIR(Game::Command::DOWN);
  else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	  pointer->set_DIR(Game::Command::RIGHT);
	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	  pointer->set_DIR(Game::Command::LEFT);
  else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    pointer->set_DIR(Game::Command::PAUSE);
  else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
    pointer->set_DIR(Game::Command::PREVLIB);
	else if (key == GLFW_KEY_4 && action == GLFW_PRESS)
	  pointer->set_DIR(Game::Command::NEXTLIB);
	else if (key == GLFW_KEY_8 && action == GLFW_PRESS)
	  pointer->set_DIR(Game::Command::RESTART);
  glm::vec3 direction(
	  cos(pointer->getVerticalAngle()) * sin(pointer->getHorizontalAngle()),
	  sin(pointer->getVerticalAngle()),
	  cos(pointer->getVerticalAngle()) * cos(pointer->getHorizontalAngle())
  );
  glm::vec3 right = glm::vec3(
	  sin(pointer->getHorizontalAngle() - 3.14f/2.0f),
	  0,
	  cos(pointer->getHorizontalAngle() - 3.14f/2.0f)
  );
  if (key == GLFW_KEY_W && action == GLFW_PRESS)
    pointer->setPosition(pointer->getPosition() + (direction * deltaTime * 0.01f));
  else if (key == GLFW_KEY_A && action == GLFW_PRESS)
      pointer->setPosition(pointer->getPosition() - (right * deltaTime * 0.01f));
    else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	pointer->setPosition(pointer->getPosition() - (direction * deltaTime * 0.01f));
      else if (key == GLFW_KEY_D && action == GLFW_PRESS)
	  pointer->setPosition(pointer->getPosition() + (right * deltaTime * 0.01f));
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
  OpenGl *pointer = (OpenGl*) glfwGetWindowUserPointer(window);

  pointer->setHorizontalAngle(pointer->getHorizontalAngle() + (pointer->getMouseSpeed() * float(pointer->getWidth()/2 - xpos)));
  pointer->setVerticalAngle(pointer->getVerticalAngle() + (pointer->getMouseSpeed() * float( pointer->getHeight()/2 - ypos )));
  glfwSetCursorPos(window, pointer->getWidth()/2, pointer->getHeight()/2);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  OpenGl *pointer = (OpenGl*) glfwGetWindowUserPointer(window);

  (void)xoffset;
  if (pointer->getFoV() >= 30.0f && pointer->getFoV() <= 50.0f)
    pointer->setFoV((float) (pointer->getFoV() - (yoffset / 3)));
  if (pointer->getFoV() <= 30.0f)
    pointer->setFoV(30.0f);
  if (pointer->getFoV() >= 50.0f)
    pointer->setFoV(50.0f);
}

OpenGl::OpenGl() {}

void OpenGl::Init_GUI()
{
  if (!glfwInit())
    {
      std::cerr << "Failed to initialize GLFW" << std::endl;
      exit(84);
    }
  glfwWindowHint(GLFW_SAMPLES, 16);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  glfwWindowHint(GLFW_RED_BITS, mode->redBits);
  glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
  glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
  glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
  Width = (GLuint) mode->width;
  Height = (GLuint) mode->height;
  window = glfwCreateWindow(Width, Height, "ARCADE", glfwGetPrimaryMonitor(),NULL);
  if (window == NULL )
    {
      std::cerr << "Failed to create GLFW window." << std::endl;
      glfwTerminate();
      exit(84);
    }
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);
  glfwSetWindowUserPointer(window, this);
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)
    {
      std::cerr << "Failed to initialize GLEW" << std::endl;
      glfwTerminate();
      exit(84);
    }
  glViewport(0, 0, Width, Height);
  glClearColor(0.156862745f, 0.0f, 0.31372549f, 0.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);
  glGenVertexArrays(1, &this->VertexArrayID);
  glBindVertexArray(this->VertexArrayID);
  _DIR = Game::Command::NONE;
  initFont("./GUIs/OpenGL/image_and_model/font.DDS");
}

std::string OpenGl::Launcher(std::vector<t_directory> v)
{
  int cursor = 0;
  int nb_games = (int) v.size();
  std::string          string;

  string.clear();
  if (nb_games > 0)
    nb_games--;
  while (glfwWindowShouldClose(window) == 0 && glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS)
    {
      glfwWaitEvents();
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      if (_DIR == Game::Command::UP)
	{
	  cursor--;
	  if (cursor < 0)
	    cursor = nb_games;
	  _DIR = Game::Command::NONE;
	}
      else if (_DIR == Game::Command::DOWN)
	  {
	    cursor++;
	    if (cursor > nb_games)
	      cursor = 0;
	    _DIR = Game::Command::NONE;
	  }
	else if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
	    {
	      glfwTerminate();
	      return (v[cursor].path);
	    }
      printGames(v, cursor);
      glfwSwapBuffers(window);
    }
  glfwTerminate();
  return (string);
}

void OpenGl::printGames(std::vector<t_directory> v, int cursor)
{
  int x = 200;
  int y = 400;
  int j = 0;

  for (std::vector<t_directory>::iterator i = v.begin(); i!= v.end(); ++i)
    {
      if (j == cursor)
	{
	  printFont(">", x - 10, y, 30);
	  printFont(i->name.c_str(), x + 10, y, 30);
	}
      else
	printFont(i->name.c_str(), x, y, 30);
      y -= 40;
      j++;
    }
}

void OpenGl::Init_Game(int y, int x)
{
  (void)x;
  (void)y;
  if( !glfwInit() )
    {
      std::cerr << "Failed to initialize GLFW" << std::endl;
      exit(84);
    }
  glfwWindowHint(GLFW_SAMPLES, 16);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  glfwWindowHint(GLFW_RED_BITS, mode->redBits);
  glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
  glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
  glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
  Width  = (GLuint) mode->width;
  Height = (GLuint) mode->height;
  window = glfwCreateWindow(Width, Height, "ARCADE", glfwGetPrimaryMonitor(), NULL);
  if( window == NULL ){
      std::cerr << "Failed to open GLFW window." << std::endl;
      glfwTerminate();
      exit(84);
    }
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetWindowUserPointer(window, this);
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
      std::cerr << "Failed to initialize GLEW" << std::endl;
      glfwTerminate();
      exit(84);
    }
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glViewport(0, 0, Width, Height);
  glClearColor(0.156862745f, 0.0f, 0.31372549f, 0.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);

  Shader newShader("./GUIs/OpenGL/ModelVertexShader.glsl", "./GUIs/OpenGL/ModelFragmentShader.glsl");
  modelShader = newShader;
  Model	newModel((GLchar *) "./GUIs/OpenGL/image_and_model/apple.obj");
  apple = newModel;
  Model	bModel((GLchar *) "./GUIs/OpenGL/image_and_model/SphereSnake.obj");
  body = bModel;
  Model	hModel((GLchar *) "./GUIs/OpenGL/image_and_model/Head.obj");
  head = hModel;
  Model grounModel((GLchar *) "./GUIs/OpenGL/image_and_model/ground.obj");
  ground = grounModel;
  Model wModel((GLchar* ) "./GUIs/OpenGL/image_and_model/Wall.obj");
  Wall = wModel;
  Model pModel((GLchar* ) "./GUIs/OpenGL/image_and_model/Pacman.obj");
  Pacman = pModel;
  Model fModel((GLchar* ) "./GUIs/OpenGL/image_and_model/Pacgom.obj");
  Food = fModel;
  Model cModel((GLchar* ) "./GUIs/OpenGL/image_and_model/cherry.obj");
  Cherry = cModel;
  Model ghModel((GLchar* ) "./GUIs/OpenGL/image_and_model/ghost.obj");
  pacGhost = ghModel;
  Model DeadModel((GLchar* ) "./GUIs/OpenGL/image_and_model/SphereSnake.obj");
  Deadghost = DeadModel;
  position = glm::vec3( 0, -2.5f, 2);
  horizontalAngle = 3.14f;
  verticalAngle = 0.8f;
  FoV = 45.0f;
  speed = 3.0f;
  mouseSpeed = 0.0005f;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  modelShader.Use();
  game_view();
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(Projection));
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(View));
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
  ground.Draw(modelShader);
  glfwPollEvents();
  glfwSwapBuffers(window);
  glGenVertexArrays(1, &this->VertexArrayID);
  glBindVertexArray(this->VertexArrayID);
  initFont("./GUIs/OpenGL/image_and_model/font.DDS");
  _DIR = Game::Command::NONE;
}

void OpenGl::S_Circle(int y, int x)
{
  float og_y = y;
  float og_x = x;

  og_y = (og_y / 10) - 1.5f;
  og_x = (og_x / 10) - 1.5f;
  modelShader.Use();
  game_view();
  model = glm::translate(model, glm::vec3(og_x, og_y, 0.05f));
  glm::mat4 Scale = glm::scale(glm::vec3(1.3f, 1.3f, 1.1f));
  model *= Scale;

  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(Projection));
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(View));
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
  body.Draw(modelShader);
}

void OpenGl::B_Dot(int y, int x)
{
  float og_y = y;
  float og_x = x;
  static float angle_z = 0;

  og_y = (og_y / 10) - 1.5f;
  og_x = (og_x / 10) - 1.5f;
  modelShader.Use();
  game_view();
  model = glm::translate(model, glm::vec3(og_x, og_y, 0.05f));
  glm::mat4 Rotate = glm::rotate(angle_z, glm::vec3(0.0f,0.0f,1.0f));
  model*= Rotate;

  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(Projection));
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(View));
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
  Cherry.Draw(modelShader);
  angle_z+=0.02f;
  if (angle_z >= 360)
    angle_z = 0;
}

void OpenGl::B_Circle(int y, int x, Game::Command command)
{
  float og_y = y;
  float og_x = x;

  og_y = (og_y / 10) - 1.5f;
  og_x = (og_x / 10) - 1.5f;
  modelShader.Use();
  game_view();
  model = glm::translate(model, glm::vec3(og_x, og_y, 0.0f));
  if (command == Game::Command::DOWN)
    {
      model = glm::translate(model, glm::vec3(0.04f, -0.06f, 0.0f));
      glm::mat4 Rotate = glm::rotate(180.0f, glm::vec3(0,0.0f,1.0f));
      model *= Rotate;
    }
  else if (command == Game::Command::RIGHT)
      {
	model = glm::translate(model, glm::vec3(-0.05f, -0.08f, 0.0f));
	glm::mat4 Rotate = glm::rotate(90.0f, glm::vec3(0.0f,0.0f,1.0f));
	model *= Rotate;
      }
    else if (command == Game::Command::LEFT)
	{
	  model = glm::translate(model, glm::vec3(0.05f, -0.07f, 0.0f));
	  glm::mat4 Rotate = glm::rotate(-90.0f, glm::vec3(0.0f,0.0f,1.0f));
	  model *= Rotate;
	}
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(Projection));
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(View));
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
  head.Draw(modelShader);
}

void OpenGl::S_Star(int y, int x)
{
  static float angle_z = 0;
  float og_y = y;
  float og_x = x;

  og_y = (og_y / 10) - 1.5f;
  og_x = (og_x / 10) - 1.5f;
  modelShader.Use();
  game_view();
  model = glm::translate(model, glm::vec3(og_x, og_y, 0.0f));
  glm::mat4 Rotate = glm::rotate(angle_z, glm::vec3(0.0f,0.0f,1.0f));
  model*= Rotate;

  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(Projection));
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(View));
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
  apple.Draw(modelShader);
  angle_z+=0.04f;
  if (angle_z >= 360)
    angle_z = 0;
}

void OpenGl::game_view()
{
  glm::vec3 direction(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));
  glm::vec3 right = glm::vec3(sin(horizontalAngle - 3.14f/2.0f), 0, cos(horizontalAngle - 3.14f/2.0f));
  glm::vec3 up = glm::cross(right, direction);
  Projection = glm::perspective(FoV, 16.0f / 9.0f, 0.1f, 100.0f);
  View       = glm::lookAt( position, position+direction, up);
  model = glm::mat4(1.0);
}

void OpenGl::Keyboard()
{
  glfwPollEvents();
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    _DIR = Game::Command::DOWN;
  else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      _DIR = Game::Command::ESCAPE;
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	_DIR = Game::Command::UP;
      else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	  _DIR = Game::Command::RIGHT;
	else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	    _DIR = Game::Command::LEFT;
}

OpenGl::~OpenGl()
{
  glfwTerminate();
}

void OpenGl::DISPLAY_Score(int score)
{
  std::stringstream ss;
  ss << score;
  std::string str = ss.str();
  glBindVertexArray(this->VertexArrayID);
  printFont("SCORE :", 0, 20, 10);
  printFont(str, 0, 10, 10);
  glBindVertexArray(0);
}

void OpenGl::Clear_WIN() {glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  glfwTerminate();}

void OpenGl::DISPLAY_Level(int level)
{
  std::stringstream ss;
  ss << level;
  std::string str = ss.str();
  glBindVertexArray(this->VertexArrayID);
  printFont("LEVEL :", 0, 50, 10);
  printFont(str, 0, 40, 10);
  glBindVertexArray(0);
}

Game::Command OpenGl::GET_key() {return(_DIR);}

void OpenGl::Refresh()
{
  glfwSwapBuffers(window);
  glfwPollEvents();
}

void OpenGl::set_DIR(Game::Command _DIR)
{
  OpenGl::_DIR = _DIR;
}

void OpenGl::setHorizontalAngle(float horizontalAngle)
{
  OpenGl::horizontalAngle = horizontalAngle;
}

void OpenGl::setVerticalAngle(float verticalAngle)
{
  OpenGl::verticalAngle = verticalAngle;
}

float OpenGl::getHorizontalAngle() const
{
  return horizontalAngle;
}

float OpenGl::getVerticalAngle() const
{
  return verticalAngle;
}

float OpenGl::getMouseSpeed() const
{
  return mouseSpeed;
}

void OpenGl::setMouseSpeed(float mouseSpeed)
{
  OpenGl::mouseSpeed = mouseSpeed;
}

const glm::vec3 &OpenGl::getPosition() const
{
  return position;
}

void OpenGl::setPosition(const glm::vec3 &position)
{
  OpenGl::position = position;
}

float OpenGl::getFoV() const
{
  return FoV;
}

void OpenGl::setFoV(float FoV)
{
  OpenGl::FoV = FoV;
}

void OpenGl::B_Block(int y, int x)
{
  float og_y = y;
  float og_x = x;

  og_y = (og_y / 10) - 1.5f;
  og_x = (og_x / 10) - 1.5f;
  modelShader.Use();
  game_view();
  model = glm::translate(model, glm::vec3(og_x, og_y, 0.0f));

  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(Projection));
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(View));
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
  Wall.Draw(modelShader);
}

void OpenGl::S_Dot(int y, int x)
{
  float og_y = y;
  float og_x = x;

  og_y = (og_y / 10) - 1.5f;
  og_x = (og_x / 10) - 1.5f;
  modelShader.Use();
  game_view();
  model = glm::translate(model, glm::vec3(og_x, og_y, 0.0f));

  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(Projection));
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(View));
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
  Food.Draw(modelShader);
}

void OpenGl::B_Circle_Yellow(int y, int x, Game::Command command)
{
  float og_y = y;
  float og_x = x;

  og_y = (og_y / 10) - 1.5f;
  og_x = (og_x / 10) - 1.5f;
  modelShader.Use();
  game_view();
  model = glm::translate(model, glm::vec3(og_x, og_y, 0.0f));
  if (command == Game::Command::DOWN)
    {
      model = glm::translate(model, glm::vec3(0.04f, -0.06f, 0.0f));
      glm::mat4 Rotate = glm::rotate(180.0f, glm::vec3(0,0.0f,1.0f));
      model *= Rotate;
    }
  else if (command == Game::Command::RIGHT)
      {
	model = glm::translate(model, glm::vec3(-0.05f, -0.08f, 0.0f));
	glm::mat4 Rotate = glm::rotate(90.0f, glm::vec3(0.0f,0.0f,1.0f));
	model *= Rotate;
      }
    else if (command == Game::Command::LEFT)
	{
	  model = glm::translate(model, glm::vec3(0.05f, -0.07f, 0.0f));
	  glm::mat4 Rotate = glm::rotate(-90.0f, glm::vec3(0.0f,0.0f,1.0f));
	  model *= Rotate;
	}
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(Projection));
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(View));
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
  Pacman.Draw(modelShader);
}

void OpenGl::DISPLAY_background(std::string &path)
{
  (void)path;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  modelShader.Use();
  game_view();
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(Projection));
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(View));
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
  ground.Draw(modelShader);
}

void OpenGl::Dead_Ghost(int y, int x)
{
  float og_y = y;
  float og_x = x;

  og_y = (og_y / 10) - 1.5f;
  og_x = (og_x / 10) - 1.5f;
  modelShader.Use();
  game_view();
  model = glm::translate(model, glm::vec3(og_x, og_y, 0.0f));

  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(Projection));
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(View));
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
  Deadghost.Draw(modelShader);
}

void OpenGl::Ghost(int y, int x, int type)
{
  float og_y = y;
  float og_x = x;

  (void)type;
  og_y = (og_y / 10) - 1.5f;
  og_x = (og_x / 10) - 1.5f;
  modelShader.Use();
  game_view();
  model = glm::translate(model, glm::vec3(og_x, og_y, 0.0f));
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(Projection));
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(View));
  glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
  pacGhost.Draw(modelShader);
}

GLuint OpenGl::getWidth() const
{
  return Width;
}

void OpenGl::setWidth(GLuint Width)
{
  OpenGl::Width = Width;
}

GLuint OpenGl::getHeight() const
{
  return Height;
}

void OpenGl::setHeight(GLuint Height)
{
  OpenGl::Height = Height;
}

extern "C" OpenGl* C_LIB()
{
  return (new OpenGl());
}
