﻿#pragma once

#include <Math/Color.h>
#include <Math/IntPoint.h>
#include <Math/IntVector.h>
#include <Math/Vector2D.h>
#include <Math/Vector4.h>
#include <Misc/AssertionMacros.h>

#define IM_ASSERT(Expr) ensure(Expr)

#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS
#define IMGUI_DISABLE_OBSOLETE_KEYIO
#define IMGUI_DISABLE_WIN32_FUNCTIONS
#define IMGUI_DISABLE_DEFAULT_ALLOCATORS
// #TODO(Ves): IMGUI_DISABLE_DEFAULT_FILE_FUNCTIONS

#define IM_VEC2_CLASS_EXTRA \
	operator FVector2f() const { return FVector2f(x, y); } \
	constexpr ImVec2(const FVector2f& V) : x(V.X), y(V.Y) {} \
	operator FVector2d() const { return FVector2d(x, y); } \
	constexpr ImVec2(const FVector2d& V) : x(V.X), y(V.Y) {} \
	operator FIntPoint() const { return FIntPoint(x, y); } \
	constexpr ImVec2(const FIntPoint& V) : x(V.X), y(V.Y) {}

#define IM_VEC4_CLASS_EXTRA \
	operator FVector4() const { return FVector4(x, y, z, w); } \
	constexpr ImVec4(const FVector4& V) : x(V.X), y(V.Y), z(V.Z), w(V.W) {} \
	operator FIntVector4() const { return FIntVector4(x, y, z, w); } \
	constexpr ImVec4(const FIntVector4& V) : x(V.X), y(V.Y), z(V.Z), w(V.W) {} \
	operator FLinearColor() const { return FLinearColor(x, y, z, w); } \
	constexpr ImVec4(const FLinearColor& C) : x(C.R), y(C.G), z(C.B), w(C.A) {}

#define ImTextureID class UTexture2D*

struct ImGuiContext;
enum ImGuiKey : int;
struct FKey;

namespace ImGui
{
	/// Helper to safely switch ImGui contexts in the current scope; in most cases you
	/// should use the default constructor to switch to the appropriate PIE context:
	/// @code
	///	ImGui::FScopedContextSwitcher ContextSwitcher;
	///	if (ContextSwitcher)
	///	{
	///		ImGui::ShowDemoWindow();
	///	}
	/// @endcode
	struct IMGUI_API FScopedContextSwitcher
	{
		UE_NODISCARD_CTOR explicit FScopedContextSwitcher(const int32 PieInstance = GPlayInEditorID);
		UE_NODISCARD_CTOR explicit FScopedContextSwitcher(ImGuiContext* Context);
		~FScopedContextSwitcher();

		/// Returns true if the current ImGui context is valid
		explicit operator bool() const;

	private:
		ImGuiContext* PrevContext = nullptr;
	};

	/// Converts between Unreal and ImGui key types
	IMGUI_API ImGuiKey ConvertKey(const FKey& Key);

	/// Converts between Unreal and ImGui 32-bit color types
	IMGUI_API FColor ConvertColor(uint32 Color);
}
