
#include "ChessGame.h"
#include "PieceFactory.h"
#include "RayIntersectionTest.h"

#include <algorithm>

#define MOVE_SPEED	0.1f

int ChessGame::size_of_tile = 5;

const glm::vec3 ChessGame::moveUp(0.0f, 0.0f, MOVE_SPEED);
const glm::vec3 ChessGame::moveDown(0.0, 0.0f, -MOVE_SPEED);
const glm::vec3 ChessGame::moveLeft(MOVE_SPEED, 0.0f, 0.0f);
const glm::vec3 ChessGame::moveRight(-MOVE_SPEED, 0.0f, 0.0f);

const glm::vec3 ChessGame::rayUp(0.0, 0.0f, size_of_tile/2.f);
const glm::vec3 ChessGame::rayDown(0.0, 0.0f, -size_of_tile/2.f);
const glm::vec3 ChessGame::rayLeft(size_of_tile/2.f, 0.0f, 0.0f);
const glm::vec3 ChessGame::rayRight(-size_of_tile/2.f, 0.0f, 0.0f);

ChessGame::ChessGame() {
    setup_light_and_material();
    build_chess_board();
    build_chess_pieces();
    add_extra_board_layer();
}


ChessPiece* ChessGame::getChessPiecesAt(int idx) {
    return _pieces[idx];
}
#define PC_SCALE	4.5f
#define PC_OFFSET_X	0.5f
#define PC_OFFSET_Z 0.5f

void ChessGame::build_chess_board() {

    // list board along x then goes up to z
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {

            ChessPiece* t = PieceFactory::get("tile");


            if((i + j) % 2 == 0 ) {
                t->setApperance(*(getWhiteTileAppearance()));
            } else {
                t->setApperance(*(getBlackTileAppearance()));
            }

            t->init();

            glm::vec3 loc(size_of_tile/2 + j*size_of_tile + PC_OFFSET_X, 0.0f, size_of_tile*i + size_of_tile/2 + PC_OFFSET_Z);
            t->setLocation(loc);
            glm::mat4 tranform =  glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::translate(glm::vec3(j*size_of_tile,  i*size_of_tile, 0)) * glm::scale(glm::vec3(5.0, 5.0f, 5.0f));;
            t->setMatrix(tranform);

            _tiles.push_back(t);

        }

    }
}

void ChessGame::build_chess_pieces() {
    // generate pawns
    for (size_t i = 0; i < 8; i++) {
        ChessPiece* pawn1 = PieceFactory::get("pawn");

        pawn1->setApperance(*(getSet1Appearance()));
        pawn1->init();

        // pawn is at second line
		glm::vec3 loc(size_of_tile/2 + i*size_of_tile + PC_OFFSET_X, 0.0f, size_of_tile + size_of_tile/2 + PC_OFFSET_Z);
        glm::mat4 tranform = glm::translate(loc) * glm::scale(glm::vec3(PC_SCALE, PC_SCALE, PC_SCALE));
        pawn1->setMatrix(tranform);
		pawn1->setLocation(loc);
		pawn1->setPlayer(1);

        _pieces.push_back(pawn1);

        ChessPiece* pawn2 = PieceFactory::get("pawn");

        pawn2->setApperance(*(getSet2Appearance()));
        pawn2->init();

        // pawn is at second line
		loc = glm::vec3(size_of_tile/2 + i*size_of_tile + PC_OFFSET_X, 0.0f, size_of_tile*6 + size_of_tile/2 + PC_OFFSET_Z);
        glm::mat4 tranform2 = glm::translate(loc) * glm::scale(glm::vec3(PC_SCALE, PC_SCALE, PC_SCALE));
		pawn2->setMatrix(tranform2);
		pawn2->setLocation(loc);
		pawn2->setPlayer(2);

        _pieces.push_back(pawn2);
    }

    // generate others
    string type;
    for (size_t i = 0; i < 8; i++) {
        if(i == 0 || i == 7) type = "rook";
        else if(i == 1 || i == 6) type = "knight";
        else if(i == 2 || i == 5) type = "bishop";
        else if(i == 3) type = "king";
        else type = "queen";

        ChessPiece* p1 = PieceFactory::get(type);

        p1->setApperance(*(getSet1Appearance()));
        p1->init();

		// pawn is at second line
		glm::vec3 loc(size_of_tile/2 + i*size_of_tile + PC_OFFSET_X, 0.0f, size_of_tile/2 + PC_OFFSET_Z);
        glm::mat4 tranform = glm::translate(loc) * glm::scale(glm::vec3(PC_SCALE, PC_SCALE, PC_SCALE));
		p1->setMatrix(tranform);
		p1->setLocation(loc);
		p1->setPlayer(1);

        _pieces.push_back(p1);

        ChessPiece* p2 = PieceFactory::get(type);

        p2->setApperance(*(getSet2Appearance()));
        p2->init();

        // pawn is at second line
		loc = glm::vec3(size_of_tile/2 + i*size_of_tile + PC_OFFSET_X, 0.0f, size_of_tile*7 + size_of_tile/2 + PC_OFFSET_Z);
        glm::mat4 tranform2 = glm::translate(loc) * glm::scale(glm::vec3(PC_SCALE, PC_SCALE, PC_SCALE));
		p2->setMatrix(tranform2);
		p2->setLocation(loc);
		p2->setPlayer(2);

        _pieces.push_back(p2);
    }
}


void ChessGame::draw() {
    for(int i=0; i<_tiles.size(); i++)
    {
        ChessPiece* tile = _tiles[i];
        tile->draw();
    }

    for(int i=0; i<_pieces.size(); i++)
    {
        ChessPiece* piece = _pieces[i];
        piece->draw();
    }

    draw_extra_layer();

    handle_animation();

}


void ChessGame::initPicking() {
    glLoadIdentity();
    glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

    for(int i=0; i<_tiles.size(); i++)
    {
        ChessPiece* tile = _tiles[i];
        setInitPicking(tile);
    }


    for(int i=0; i<_pieces.size(); i++)
    {
        ChessPiece* piece = _pieces[i];
        setInitPicking(piece);
    }

}

void ChessGame::setInitPicking(ChessPiece* piece) {
    ObjectId *oid = piece->getObjectId();
    glUseProgram(piece->getProgram());
	int l0 = glGetUniformLocation(piece->getProgram(), "select_mode");
	int sel0 = glGetUniformLocation(piece->getProgram(), "is_selected");
	int coll0 = glGetUniformLocation(piece->getProgram(), "is_collision");
	glUniform1i(l0, false);
	glUniform1i(sel0, false);
	glUniform1i(coll0, false);
    glUniform4f( glGetUniformLocation(piece->getProgram(), "select_color_id"), oid->r, oid->g, oid->b,1.0 );
}


void ChessGame::preDrawPicking() {

    for(int i=0; i<_tiles.size(); i++)
    {
        ChessPiece* piece = _tiles[i];
        setPreDrawPicking(piece);
    }

    for(int i=0; i<_pieces.size(); i++)
    {
        ChessPiece* piece = _pieces[i];
        setPreDrawPicking(piece);
    }
}

void ChessGame::setPreDrawPicking(ChessPiece *piece) {
    glUseProgram(piece->getProgram());
    int l0 = glGetUniformLocation(piece->getProgram(), "select_mode");
//    int sel0 = glGetUniformLocation(piece->getProgram(), "is_selected");
    glUniform1i(l0, true);

    // render
    piece->draw();
    glUniform1i(l0, false); // and switch to regular mode.

}

void ChessGame::handleSelectedColor(float col[4]) {
    int id = ObjectIdFactory::getIdFromColor(col);

    ChessPiece* p = getObjectById(id);

    if(_selected_piece != NULL && _selected_piece != _clicked_piece && _selected_piece != _clicked_tile) { // some thing is already selected
        unhighlightAPiece(_selected_piece); // un highligh it
    }

    if(p != NULL) {
        // cout << id << "--" << col[0] << col[1] << col[2]<< endl;
        // unhighlightAPiece(_selected_piece);

        _selected_piece = p;
        highlightAPiece(p);

    } else {

    }

}
void ChessGame::unhighlightAPiece(ChessPiece *p) {
	glUseProgram(p->getProgram());
	int uniform_id = glGetUniformLocation(p->getProgram(), "is_selected");

	glUniform1i(uniform_id, false);

	glUseProgram(0);
}

void ChessGame::highlightAPiece(ChessPiece *p) {
	glUseProgram(p->getProgram());
	int uniform_id = glGetUniformLocation(p->getProgram(), "is_selected");

	glUniform1i(uniform_id, true);

	glUseProgram(0);
}

void ChessGame::unhighlightCollision(ChessPiece *p) {
	glUseProgram(p->getProgram());
	int uniform_id = glGetUniformLocation(p->getProgram(), "is_collision");

	glUniform1i(uniform_id, false);

	glUseProgram(0);
}

void ChessGame::highlightCollision(ChessPiece *p) {
	glUseProgram(p->getProgram());
	int uniform_id = glGetUniformLocation(p->getProgram(), "is_collision");

	glUniform1i(uniform_id, true);

	glUseProgram(0);
}

ChessPiece* ChessGame::getObjectById(int id) {

    for(int i=0; i<_pieces.size(); i++)
    {
        ChessPiece* piece = _pieces[i];
        if(piece->getObjectId()->id == id) return piece;
    }

    for(int i=0; i<_tiles.size(); i++)
    {
        ChessPiece* piece = _tiles[i];
        if(piece->getObjectId()->id == id) return piece;
    }

    return NULL;

}

void ChessGame::movePiece(ChessPiece *current_pos, ChessPiece * to_pos){

    _animating_piece = current_pos;
    _destination_tile = to_pos;

    // interpolating the intermediate locations
    //current_pos->moveToLocation(to_pos->getLocation());
}

void ChessGame::handleMouseRelease() {
    if(_selected_piece == NULL) {
        _clicked_piece = NULL;
        _clicked_tile = NULL;
        return;
    }

    if(_clicked_piece !=NULL && _selected_piece->getType() == "tile") { // click on tile
        if(_clicked_tile) unhighlightAPiece(_clicked_tile);

        _clicked_tile = _selected_piece;
        movePiece(_clicked_piece, _clicked_tile);
        //_clicked_piece->moveToLocation(_clicked_tile->getLocation());

    } else if (_selected_piece->getType() != "tile") { // click on a piece
        if(_clicked_piece) unhighlightAPiece(_clicked_piece);
        if(_clicked_tile) unhighlightAPiece(_clicked_tile);

        _clicked_piece = _selected_piece;
        // highlightAPiece(_clicked_piece);

    }
}

void ChessGame::handleKeyPress(int key, int action) {
	bool move = false;

	if (_clicked_piece)
	{
		if(key == GLFW_KEY_UP)
		{
			_clicked_piece->translatePiece(moveUp);
			move = true;
		}
		else if(key == GLFW_KEY_DOWN)
		{
			_clicked_piece->translatePiece(moveDown);
			move = true;
		}
		else if(key == GLFW_KEY_LEFT)
		{
			_clicked_piece->translatePiece(moveLeft);
			move = true;
		}
		else if(key == GLFW_KEY_RIGHT)
		{
			_clicked_piece->translatePiece(moveRight);
			move = true;
		}

		if(move)
		{
			handleCollision();
		}
	}
}

void ChessGame::handleCollision(){
    bool collision = false;
    int count = 0;
    for (int i = 0; i < _pieces.size(); i++)
    {
        collision = false;
        ChessPiece *p = _pieces[i];
        glm::vec3 s = _clicked_piece->getLocation();
        s += glm::vec3(0.f, .1f, .0f);

        if (p->getPlayer() != _clicked_piece->getPlayer() &&
            sqrt(pow(s.x - p->getLocation().x,2) + pow(s.z - p->getLocation().z,2)) < size_of_tile)
        {
            _intersectList.clear();
            count++;

            // Up, down, left, right rays
            glm::vec3 e = s + rayUp;
            if (RayIntersectionTest::intersect(s, e, *p, _intersectList)) {
                //cout << p->getLocation().x << " " << p->getLocation().z << ",  ";
                collision = true;
            }

            e = s + rayDown;
            if (RayIntersectionTest::intersect(s, e, *p, _intersectList)) {
                //cout << p->getLocation().x << " " << p->getLocation().z << ",  ";
                collision = true;
            }

            e = s + rayLeft;
            if (RayIntersectionTest::intersect(s, e, *p, _intersectList)) {
                //cout << p->getLocation().x << " " << p->getLocation().z << ",  ";
                collision = true;
            }

            e = s + rayRight;
            if (RayIntersectionTest::intersect(s, e, *p, _intersectList)) {
                //cout << p->getLocation().x << " " << p->getLocation().z << ",  ";
                collision = true;
            }

            // Diagonal rays (Comment if too slow)
            e = s + (sqrt(2.f)/2.f) * (rayUp + rayRight);
            if (RayIntersectionTest::intersect(s, e, *p, _intersectList)) {
                //cout << p->getLocation().x << " " << p->getLocation().z << ",  ";
                collision = true;
            }

            e = s + (sqrt(2.f)/2.f) * (rayDown + rayRight);
            if (RayIntersectionTest::intersect(s, e, *p, _intersectList)) {
                //cout << p->getLocation().x << " " << p->getLocation().z << ",  ";
                collision = true;
            }

            e = s + (sqrt(2.f)/2.f) * (rayDown + rayLeft);
            if (RayIntersectionTest::intersect(s, e, *p, _intersectList)) {
                //cout << p->getLocation().x << " " << p->getLocation().z << ",  ";
                collision = true;
            }

            e = s + (sqrt(2.f)/2.f) * (rayUp + rayLeft);
            if (RayIntersectionTest::intersect(s, e, *p, _intersectList)) {
                //cout << p->getLocation().x << " " << p->getLocation().z << ",  ";
                collision = true;
            }
        }

        if (collision)
        {
            highlightCollision(p);
            _pieces.erase(_pieces.begin()+i);
        } else {
            unhighlightCollision(p);
        }
    }
    //cout << endl << "# pieces checked: " << count << endl;
}


void ChessGame::handle_animation() {
    if(_animating_piece == NULL || _destination_tile == NULL) return;

    glm::vec3 direction = _destination_tile->getLocation()-_animating_piece->getLocation();
    direction = direction.operator/=(100);

    if((_animating_piece->getLocation().x) - (_destination_tile->getLocation().x) >0.1 || (_destination_tile->getLocation().x) - (_animating_piece->getLocation().x) <-0.1 ||
          (_destination_tile->getLocation().y) - (_animating_piece->getLocation().y) >0.1 || (_destination_tile->getLocation().y) - (_animating_piece->getLocation().y) <-0.1 ||
          (_destination_tile->getLocation().z) - (_animating_piece->getLocation().z) >0.1 || (_destination_tile->getLocation().z) - (_animating_piece->getLocation().z) <-0.1
          ){
       _animating_piece->translatePiece(direction);
        handleCollision();
    } else {
        _animating_piece = NULL;
        _destination_tile = NULL;
    }

}
