# HCI-557-CG Final projections
Members: Matthew Gardner, Minh Truong, Tianshuang Gao, Jiale Feng

## Model
Chess pieces are separate objects loaded from obj files with complex object surface with about ten thousands surfaces per piece. Objects are loaded without any material, all colors and lightings on each object are handled by our own texture and lighting code.

## Texture and Lighting
Each chess piece has multiple lightings to make it distinguishable from other pieces. We use only direct light and multiple spotlights to create our expected effect.

Instead of mixing multiple texture together with the chess board, its layout is built by combining two layers. First layer is the original board with clickable tiles and black and white color for each tile. Another layer just above the first one is a multi texture layer combined with bump mapping and is made transparent so that we can still see and click on the first layer. The multi texture layer reuses some source code from instructor and combined with our own noise map and some adjustment in the noise function to create a water like effect. The result is a board cover with moving water.

## Picking
We implement picking by treating each piece and tile in the game as separate objects. Each object is assigned an ID ranging from 1 to 999. For each ID abc, the corresponding color is Red: a, Green: b, Blue: c. So we can guarantee that color and ID are mapped 1 to 1.

To select a piece or a tile, we do not use mouse_callback but instead detecting the transition in mouse button state from PRESS to RELEASE.

 We also enforce some logic that we can only select one piece at a time and one tile at a time. If one clicks on a piece and then on a tile, we animate the chess object into the tile's location.

## Navigation & Collision detection
Collision is detected by rays sticking out multiple directions at the base of the moving piece. Collision detection is only checked with pieces that are within a distance of one tile, so potentially 4 are checked if pieces are configured properly.

A piece is first selected and then moved using the arrow keys or by selecting a tile. Opposing pieces that it comes in contact with will be "destroyed".

## Animation
One can choose a chess piece then choosing a tile and the selected piece will move toward the tile using keyframe animation. For intermediate frame locations, we simply use location in the middle of start and end location and update new location for the piece for each frame. As being described in navigation section, if having an enemy piece on the way, the piece will destroy it.

For more detail about how aforementioned features behave, refer to demo video 
