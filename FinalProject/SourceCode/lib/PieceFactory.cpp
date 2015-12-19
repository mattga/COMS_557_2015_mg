#include "PieceFactory.h"

#include <algorithm>

ChessPiece* PieceFactory::get(string type) {
    if(type == "pawn") return new ChessPiece("../../data/pawn.obj", type);

    if(type == "knight") return new ChessPiece("../../data/knight.obj", type);

    if(type == "bishop") return new ChessPiece("../../data/bishop.obj", type);

    if(type == "queen") return new ChessPiece("../../data/queen.obj", type);

    if(type == "king") return new ChessPiece("../../data/king.obj", type);

    if(type == "rook") return new ChessPiece("../../data/rook.obj", type);

    if(type == "tile") return new ChessPiece("../../data/tile.obj", type);

    return new ChessPiece();

}
