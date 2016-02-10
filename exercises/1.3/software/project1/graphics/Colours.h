// see --http://www.rapidtables.com/web/color/RGB_Color.htm for example colours

// This file creates symbolic names for the colours that you can specify in your program
// the actual RGB values are set up in the FPGA Rom, so the name BLACK for example, refer to colour
// palette number 0 whose 24 bit RGB value is 0x000000, WHITE is palette number 1 = RGB value 0xFFFFFF etc
//
// See the ColourPalette.h header file

#ifndef COLOURS_H_
#define COLOURS_H_

typedef enum  {
BLACK,
REDWINE,
FOREST,
BARF,
NAVY,
LIGHTPURPLE,
TURQUOISE,
SILVER,
HONEYDEW,
SKYBLUE,
DARKBROWN,
BURGUNDY,
REDBROWN,
BLOOD,
TOMATO,
BRIGHTRED,
PINE,
MOSS,
VERDUNGREEN1,
NUTMEGWOOD,
CINNAMON,
OREGON,
ROSESHARON1,
GRENADIER,
CAMARONE,
JAPANESELAUREL1,
VERDUNGREEN2,
VERDUNGREEN3,
OLIVE1,
CHELSEAGEM,
ROSESHARON2,
BAMBOOORANGE,
JAPANESELAUREL2,
JAPANESELAUREL3,
VERDUNGREEN4,
OLIVE2,
OLIVE3,
PIRATEGOLD1,
PIRATEGOLD2,
MANGOTANGO,
JAPANESELAUREL4,
JAPANESELAUREL5,
LIMEADE1,
LIMEADE2,
LIMEADE3,
BUDDHAGOLD1,
BUDDHAGOLD2,
TANGERINE,
GREEN2,
HARLEQUIN1,
LIMEADE4,
LIMEADE5,
PISTACHIO1,
PISTACHIO2,
BUDDHAGOLD3,
CORN,
GREEN3,
HARLEQUIN2,
HARLEQUIN3,
BRIGHTGREEN,
CHATREUSE,
RIOGRANDE1,
RIOGRANDE2,
TURBO,
STRATOS,
TOLOPEA,
BLACKBERRY,
POMPADOUR,
SIREN,
PAPRIKA,
MONZA,
REDRIBBON,
MIDNIGHT,
MIRAGE,
LIVIDBROWN,
TAWNYPORT,
CLARET,
MEXICANRED,
MAROONFLUSH,
ALIZARINCRIMSON,
CYPRUS,
TEPAPAGREEN,
TUNDORA,
KABUL,
LOTUS,
APPLEBLOSSOM,
CRAIL,
PUNCH,
FUNGREEN,
GREENPEA,
TOMTHUMB,
HEMLOCK,
SPICYMIX,
SEPIASKIN,
CRAIL2,
FLAMEPEA,
FUNGREEN2,
EUCALYPTUS,
GOBLIN,
FERNGREEN,
YELLOWMETAL,
SYCAMORE,
TUSSOK,
REDDAMASK,
GREENHAZE,
FORESTGREEN,
APPLE,
APPLE2,
SUSHI,
SYCAMORE2,
TUSSOCK2,
ANZAC,
MALACHITE,
MALACHITE2,
APPLE3,
APPLE4,
SUSHI2,
SUSHI3,
TURMERIC,
ANZAC2,
MALACHITE3,
MALACHITE4,
PASTELGREEN,
ATLANTIS,
CONIFER,
CONIFER2,
PEAR,
WATTLE,
NAVY2,
NAVY3,
PIGMENTINDIGO,
PIGMENTINDIGO2,
FRESHEGGPLANT,
FLIRT,
FLIRT2,
ROSE,
RESOLUTIONBLUE,
JACKSONSPURPLE,
METEORITE,
HONEYFLOWER,
PLUM,
HIBISCUS,
REDVIOLET,
CERISE,
CONGRESSBLUE,
BAYOFMANY,
EASTBAY,
AFFAIR,
CANNONPINK,
ROUGE,
MULBERRY,
CERISE2,
ORIENT,
BLUEMINE,
EASTBAY2,
COMET,
OLDLAVENDER,
STRIKEMASTER,
TAPESTRY,
CRANBERRY,
TEAL,
ELM,
FADEDJADE,
CUTTYSARK,
GRAY,
PHARLAP,
ABBEY,
ABBEY2,
PERSIANGREEN,
JUNGLEGREEN,
OCEANGREEN,
AQUAFOREST,
AMULET,
TALLOW,
MONGOOSE,
TUMBLEWEED,
CARRIBEANGREEN,
MOUNTAINMEADOW,
EMERALD,
FERN,
DEYORK,
OLIVINE,
PINEGLADE,
HARVESTCGOLD,
CARRIBEANGREEN2,
MOUNTAINMEADOW2,
SHAMROCK,
PASTELGREEN2,
PASTELGREEN3,
FEIJOA,
YELLOWGREEN,
CHENIN,
DARKBLUE,
DARKBLUE2,
PURPLE,
PURPLE2,
PURPLE3,
PURPLE4,
HOLLYWOODCERISE,
PURPLEPIZZAZZ,
INTERNATIONALKLEINBLUE,
PERSIANBLUE2,
PERSIANBLUE3,
PURPLEHEART,
PURPLEHEART2,
PURPLEHEART3,
REDVIOLET2,
CERISE3,
COBALT,
PERSIANBLUE4,
GOVERNORBAY,
STUDIO,
FUCHSIABLUE,
AMETHYST,
FUCHSIAPINK,
CERISE4,
SCIENCEBLUE,
MARINER,
INDIGO,
BLUEVIOLET,
FUCHSIABLUE2,
AMETHYST2,
FUCHSIAPINK2,
ORCHID,
LOCHMARA,
CURIOUSBLUE,
STEELBLUE,
STEELBLUE2,
WILDBLUEYONDER,
PURPLEMOUNTAINSMAJESTY,
VIOLA,
SHOCKING,
PACIFICBLUE,
EASTERNBLUE,
PELOROUS,
FOUNTAINBLUE,
NEPAL,
CADETBLUE,
LILAC,
LIGHTORCHID,
ROBINSEGGBLUE,
JAVA,
PELOROUS2,
FOUNTAINBLUE2,
NEPTUNE,
OPAL,
ISLANDSPICE,
SANTASGRAY,
GRAY2,
RED,
GREEN,
YELLOW,
BLUE,
MAGENTA,
CYAN,
WHITE
} Colour;

#endif /* COLOURS_H_ */
