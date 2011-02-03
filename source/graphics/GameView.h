/* Copyright (C) 2010 Wildfire Games.
 * This file is part of 0 A.D.
 *
 * 0 A.D. is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * 0 A.D. is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with 0 A.D.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INCLUDED_GAMEVIEW
#define INCLUDED_GAMEVIEW

// needed by minimap
extern float g_MaxZoomHeight;	//note:  Max terrain height is this minus YMinOffset
extern float g_YMinOffset;

#include "renderer/Scene.h"
#include "simulation2/system/Entity.h"

#include "lib/input.h" // InReaction - can't forward-declare enum

class CGame;
class CObjectManager;
class CCamera;
class CCinemaManager;
class CLOSTexture;
class CVector3D;
struct SViewPort;

struct JSObject;

class CGameViewImpl;

class CGameView : private Scene
{
	NONCOPYABLE(CGameView);
public:
	static const float defaultFOV, defaultCullFOV, defaultNear, defaultFar;

private:
	static const float cameraPivotMargin;
	CGameViewImpl* m;

	// Check whether lighting environment has changed and update vertex data if necessary
	void CheckLightEnv();

	//BEGIN: Implementation of Scene
	void EnumerateObjects(const CFrustum& frustum, SceneCollector* c);
	//END: Implementation of Scene

	// InitResources(): Load all graphics resources (textures, actor objects and
	// alpha maps) required by the game
	//void InitResources();

	// UnloadResources(): Unload all graphics resources loaded by InitResources
	void UnloadResources();

public:
	CGameView(CGame *pGame);
	~CGameView();

	void SetViewport(const SViewPort& vp);

	void RegisterInit();
	int Initialize();

	CObjectManager& GetObjectManager() const;

	// Update: Update all the view information (i.e. rotate camera, scroll,
	// whatever). This will *not* change any World information - only the
	// *presentation*
	void Update(float DeltaTime);

	// Render: Render the World
	void Render();

	InReaction HandleEvent(const SDL_Event_* ev);

	void MoveCameraTarget(const CVector3D& target, bool minimap = false);
	void ResetCameraTarget(const CVector3D& target);
	void ResetCameraAngleZoom();
	void CameraFollow(entity_id_t entity, bool firstPerson);

	CCamera *GetCamera();
	CCinemaManager* GetCinema();
	CLOSTexture& GetLOSTexture();

	JSObject* GetScript();
	static void ScriptingInit();
};
extern InReaction game_view_handler(const SDL_Event_* ev);

#endif
