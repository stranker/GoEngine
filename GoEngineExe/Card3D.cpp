#include "Card3D.h"

void Card3D::Ready() {
}

void Card3D::Update(float deltaTime) {
}

Card3D::Card3D() {
	name = "Card3D";
	SetScale(Vector3(6, 9, 1));
	spatialMaterial = ResourceManager::LoadSpatialMaterial("Shaders/SpatialMaterial.vs", "Shaders/FoilShader.fs", "cardMaterial");
	main = ResourceManager::LoadTexture("pokemon_card.png", "pokemon_card");
	noise = ResourceManager::LoadTexture("pokemon_card_noise.png", "pokemon_card_noise");
	//noise = ResourceManager::LoadTexture("card_noise_2.png", "pokemon_card_noise");
	foil = ResourceManager::LoadTexture("pokemon_card_foil.jpg", "pokemon_card_gradient");
	//foil = ResourceManager::LoadTexture("holo_gradient_1.jpg", "pokemon_card_gradient");
	mask = ResourceManager::LoadTexture("pokemon_card_mask.jpg", "pokemon_card_mask");
	if (spatialMaterial) {
		spatialMaterial->AddTexture("main_texture", main);
		spatialMaterial->AddTexture("noise_texture", noise);
		spatialMaterial->AddTexture("gradient_texture", foil);
		spatialMaterial->AddTexture("mask_texture", mask);
		spatialMaterial->AddFloat("noise_strength", 0.2f, 0.0f, 1.0f);
		spatialMaterial->AddFloat("mask_opacity", 1.0f, 0.0f, 1.0f);
		spatialMaterial->AddFloat("light_energy", 1.0f, 0.0f, 3.0f);
		spatialMaterial->AddFloat("time_mul", 0.075f, 0.0f, 0.125f);
	}
}