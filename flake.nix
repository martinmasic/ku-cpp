{
  description = "Ultimate sudoku implementation. Maybe.";

  inputs =
  {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
    ...
  } @ inputs:
  let
    system = "x86_64-linux";
    pkgs = import nixpkgs {inherit system;};
  in
  with pkgs;
  {
    # development shell
    devShells.${system}.default = mkShell {
      buildInputs =
      [
        clang_19
      ];

    };

  };

}
