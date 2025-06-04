# tutorial on NixOS: 
# 1. cd folder
# 2. cmd -> nix-shell -> code .

{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.python3Packages.jupyter
    pkgs.python3Packages.ipykernel
    pkgs.python3Packages.numpy
    pkgs.python3Packages.pandas
    pkgs.python3Packages.matplotlib
    # other packages
  ];

  shellHook = ''
    echo "Activating Jupyter Notebook environment..."

    export PYTHONPATH="${pkgs.python3Packages.ipykernel}/lib/python${pkgs.python3Packages.python.pkgs.python.version}/site-packages:$PYTHONPATH"

    ${pkgs.python3Packages.python.pkgs.python}/bin/python -m ipykernel install --user --name=nix-shell-kernel --display-name="Nix Shell Kernel"
  '';
}