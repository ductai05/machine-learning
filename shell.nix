with import <nixpkgs> {};
pkgs.mkShell {
  buildInputs = [
    python3
    python3Packages.pip
    python3Packages.face-recognition
    python3Packages.numpy
    # add other python libs
  ];
  shellHook = ''
    # add environment variable
    echo "ML notebook"
  '';
}