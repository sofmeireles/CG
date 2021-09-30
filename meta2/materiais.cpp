#include <GL\freeGlut.h>
#include "materiais.h"

void initMaterials(int material) {
	GLfloat back[] = { 0,0,0 };
	switch (material) {
	case 0: //……………………………………………………………………………………………esmerald
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, esmeraldAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, esmeraldDif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, esmeraldSpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, esmeraldCoef);
		break;
	case 1: //……………………………………………………………………………………………jade
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, jadeAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, jadeDif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, jadeSpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, jadeCoef);
		break;
	case 2: //……………………………………………………………………………………………obsidian
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, obsidianAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, obsidianDif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, obsidianSpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, obsidianCoef);
		break;
	case 3: //……………………………………………………………………………………………pearl
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pearlAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pearlDif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pearlSpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pearlCoef);
		break;
	case 4: //……………………………………………………………………………………………ruby
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, rubyAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, rubyDif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, rubySpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, rubyCoef);
		break;
	case 5: //……………………………………………………………………………………………turquoise
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, turquoiseAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, turquoiseDif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, turquoiseSpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, turquoiseCoef);
		break;
	case 6: //……………………………………………………………………………………………brass
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, brassAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brassDif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, brassSpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brassCoef);

		break;
	case 7: //……………………………………………………………………………………………bronze
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, bronzeAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, bronzeDif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, bronzeSpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, bronzeCoef);
		glMaterialfv(GL_BACK, GL_SPECULAR, back);
		break;
	case 8: //……………………………………………………………………………………………chrome
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, chromeAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, chromeDif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, chromeSpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, chromeCoef);
		glMaterialfv(GL_BACK, GL_SPECULAR, back);
		break;
	case 9: //……………………………………………………………………………………………copper
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, copperAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, copperDif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, copperSpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, copperCoef);
		glMaterialfv(GL_BACK, GL_SPECULAR, back);
		break;
	case 10: //……………………………………………………………………………………………gold
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, goldAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, goldDif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, goldSpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, goldCoef);
		break;
	case 11: //……………………………………………………………………………………………silver
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silverAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, silverDif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, silverSpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, silverCoef);
		break;
	case 12: //……………………………………………………………………………………………blackPlastic
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blackPlasticAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blackPlasticDif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, blackPlasticSpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, blackPlasticCoef);
		break;
	case 13: //……………………………………………………………………………………………cyankPlastic
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cyanPlasticAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cyanPlasticDif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cyanPlasticSpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, cyanPlasticCoef);
		break;
	case 14: //……………………………………………………………………………………………greenPlastic
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, greenPlasticAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, greenPlasticDif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, greenPlasticSpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, greenPlasticCoef);
		break;
	case 15: //……………………………………………………………………………………………redPlastic
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, redPlasticAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, redPlasticDif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, redPlasticSpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, redPlasticCoef);
		break;
	case 16: //……………………………………………………………………………………………whitePlastic
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whitePlasticAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whitePlasticDif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whitePlasticSpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, whitePlasticCoef);
		glMaterialfv(GL_BACK, GL_SPECULAR, back);
		break;
	case 17: //……………………………………………………………………………………………yellowPlastic
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, yellowPlasticAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, yellowPlasticDif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, yellowPlasticSpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, yellowPlasticCoef);
		break;
	case 18:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, vidroAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, vidroDif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, vidroSpec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, vidroCoef);
		break;

	}
}
