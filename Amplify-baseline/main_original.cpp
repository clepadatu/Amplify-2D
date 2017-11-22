#include	"private_libraries/window/window.h"
#include	"private_libraries/input/input.h"
#include	"private_libraries/maths/maths.h"
#include	"private_libraries/utils/fileutils.h"
#include	"private_libraries/graphics/shader.h"
#include	"private_libraries/graphics/buffers/buffer.h"
#include	"private_libraries/graphics/buffers/indexbuffer.h"
#include	"private_libraries/graphics/buffers/vertexarray.h"
#include	<glm.hpp>
#include	<gtc/matrix_transform.hpp>
#include	<gtx/transform.hpp>
#include	<chrono>
#include	"private_libraries\utils\controls_MVP.h"
#include	"private_libraries\utils\controls_MP.h"
#include	<SOIL.h>
#include	"private_libraries\game_objects\GameObject.h"
#include	"private_libraries\game_objects\player.h"
#include	"private_libraries\game_objects\AI.h"
#include	"private_libraries\game_objects\projectile.h"
#include    <list>



int		main()
{	
	
	//=== Declare namespaces that need to be used
	using	namespace	Erebos;
	using	namespace	graphics;
	using	namespace	maths;
	//********************************************

	//=====================================Standard Objects definition
	
	//=====================================

	int		width,	height,	type;
	//double	x,	y;
	width	=	 1280;
	height	=	 720;
	type	=	 0;

	int projectile_delay = 0;



	Window*		window	=	new		Window("Amplify",	 width,		height);
	window->WindowColor(0.0f,	0.0f,	0.0f,	0.0f);

	

	GLfloat		vertices_square[]	 =
		{
			-1.0f,	-1.0f,	 0.0f,
			1.0f,	-1.0f,	 0.0f,
			1.0f,	1.0f,	0.0f,
			-1.0f,	1.0f,	 0.0f
	
		};

	GLfloat		vertices_rectangle[]	 =
		{	
			-0.5f,		0.5f,	1.0f,	0.0f,	 0.0f, // Top-left
			0.5f,	 0.5f,	 0.0f,	 1.0f,		0.0f, // Top-right
			0.5f,	-0.5f,	 0.0f,	0.0f,	 1.0f, // Bottom-right
			-0.5f,	-0.5f,	1.0f,	1.0f,	1.0f  // Bottom-left
		};

	GLushort	indices_square[]	 =
		{
			0, 1, 2,
			2, 0, 3
		}; //bottom
		
	GLushort	 indices_rectangle[]	 =
		{
			0,	1,	2,
			2,	3,	 0
		};
	

	GLfloat		colorsA[]	 =
		{
			0.67f,	 0.3f,	0.3f,	0.2f,
			0.47f,	 0.3f,	0.3f,	0.2f,
			0.37f,	 0.3f,	0.3f,	0.2f,
			0.57f,	 0.1f,	0.9f,	0.5f
		
		};

	GLfloat		colorsB[]	 =
		{	
			0.583f,	 0.771f,	 0.014f,	 1.0f,
			0.609f,	 0.115f,	 0.436f,	 1.0f,
			0.327f,	 0.483f,	 0.844f,	 1.0f,
			1.0f,	0.0f,	0.0f,	1.0f
		
		
		};

	GLfloat texture_coordinates[] =	{
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f
	};
	
	//IndexBuffer		ibo(indices_square, 6);


	Player Player1;
	AI AI1;
	AI AI2;
	double uidz;
	std::list<Projectile> ammo;
	//glfwSetMouseButtonCallback ( (GLFWwindow*)window,  );
	
	Player1.set_vars(window, vertices_square, indices_square, colorsB, texture_coordinates);
	AI1.set_vars(window, vertices_square, indices_square, colorsB, texture_coordinates);
	AI2.set_vars(window, vertices_square, indices_square, colorsB, texture_coordinates);
	//ammo.set_vars(window, vertices_square, indices_square, colorsB, texture_coordinates);
	Player1.Initialise_controls();
	AI1.Initialise_controls();
	AI2.Initialise_controls();
	//ammo.Initialise_controls();
	Player1.Enable_shader();
	AI1.Enable_shader();
	AI2.Enable_shader();
	//ammo.Enable_shader();
	

	/*
	VertexArray		Player_ship;
	IndexBuffer		ibo		(indices_square,		6);
	//IndexBuffer		ibo2	(indices_rectangle,		6);

	Player_ship.addBuffer	(new Buffer	(vertices_square,	4 * 3,	3),		0);
	Player_ship.addBuffer	(new Buffer	(colorsB,	4 * 4,	 4),	1);
	Player_ship.addBuffer	(new Buffer (texture_coordinates, 4 * 2, 2), 2);

	
	GLuint texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int awidth, aheight;
	unsigned char* image = SOIL_load_image("private_libraries/textures/shship.png", &awidth, &aheight, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, awidth, aheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	*/

	


	//Shader shader	("private_libraries/shaders/basic.vert", "private_libraries/shaders/basic.frag");
	//shader.enable();
	
		
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	


	
	
	double current, elapsed;
	double previous = clock ( );
	double lag = 0.0;
	//window->getMousePosition(x, y);
	//Controls_MVP	control;
	//Controls_MP		control_mp	(width,height,type, x, y);

	//semi-gameloop, window.closed based
	while (!window->closed())
	{
		//window->getMousePosition(x, y);
		//std::cout << "(X,Y):" << x << "," << y << std::endl;

		//INPUTS
		//control_mp.computeMatricesFromInputs(window,x,y);
		
		//std::cout << "Elapsed=" << elapsed << std::endl;

	
		//LOGIC
		
			
		
	//Render
		//glm::mat4 MVP = control_mp.getProjectionMatrix() * control_mp.getViewMatrix()*control_mp.getModelMatrix();
		//std::cout << "Object (X,Y) is:" << MVP[3][0] << std::endl; Object space coordinate of updated model

//		glUniformMatrix4fv(shader.getUniformLocation("MVP"), 1, GL_FALSE, &MVP[0][0]);
		
		
		current = clock ( ); //start frame time snap
		elapsed = current - previous; //time elapsed between current and last frame
		previous = current;//prepare time snap for next frame
		lag += elapsed; //lag measurement
		window->clear();

		//Control
		if ( Player1.check_click ( ) )
			{
			ammo.emplace_back ( Player1.get_player_position (), Player1.get_direction_for_bullet (), 0.005f, 10000, uidz, window, vertices_square, indices_square, colorsB, texture_coordinates, uidz );
			//ammo.emplace_back ( Player1.get_player_position ( ), Player1.get_direction_for_bullet ( ), 0.005f, 10000, uidz, window, vertices_square, indices_square, colorsB, texture_coordinates,uidz );
			//uidz++;
			//ammo.back ( ).set_vars ();
			//ammo.back ( ).Initialise_controls ( );
			//ammo.back ( ).Enable_shader ( );


			};


		//ibo.bind();
		
		/*Player_ship.bind();
		ibo.bind();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(shader.getUniformLocation("Ship_texture"), 0);
		*/
	
				/*for ( int i = 0; i < ammo.size ( ); i++ )
				{
				if ( ammo [i]._To_screen ( ) == true )
					{
					ammo [i] = ammo.back ( );
					ammo.pop_back ( );
					}*/
			/*for ( int i = ammo.size()-1; i>= 0; i-- )
				{
				if ( ammo [i]._Should_draw () == true )
					{
					ammo [i]._To_screen ();
					}
				else
					{

					ammo.erase ( ammo.begin () + i );
					ammo.shrink_to_fit ();
					}
				};*/
		
		/*	if ( ammo.size() > 0 )
				{
				for ( std::list<Projectile>::iterator iterator = ammo.begin (), end = ammo.end (); iterator != end; ++iterator )
					{
					if ( iterator->_Should_draw () == true )
						{
						iterator->_To_screen ();
						}
					else
						
						{
						ammo.remove ( iterator );
						}
					}

				}
			*/
		//Update
		while ( lag >= 10 )
			{
			AI1.Update ();
			AI2.Update ();
			Player1.Update ();
			std::list<Projectile>::iterator i = ammo.begin ();
			while ( i != ammo.end () )
				{				
					(*i).Update ();
					++i;
				}
			lag -= 10;
			}

		//Render
		

			AI1.To_screen ( );

			AI2.To_screen ( );

			Player1.To_screen ( );
			std::list<Projectile>::iterator j = ammo.begin ( );
			while ( j != ammo.end ( ) )
				{
				if ( (*j)._Should_draw ( ) == true )
					{
					(*j)._To_screen ( );
					++j;
					}
				else
					{
					j = ammo.erase ( j );
					}
				}

		

			window->update ( );

			

	
		//glDrawElements(GL_TRIANGLES, Player1.ibo_count(), GL_UNSIGNED_SHORT, (void*)0);
		
	
		/*ibo.unbind();
		Player_ship.unbind();
		
		
		*/
		
		
		
		
	}

	window->~Window();
	return 0;

}