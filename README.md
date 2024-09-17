
# Chemical Equation Balancer

![Screenshot 2024-09-17 055339](https://github.com/user-attachments/assets/c1b317c4-8500-40e2-95c3-a5d43b102831)

This terminal-based C++ chemical equation balancer parses equations into vectors and balances them using row operations, supporting equations with ions and water of crystallization

## Features

- **Standard Chemical Equations:**  
  
  The program balances typical chemical reactions of the form `[Reactants] -> [Products]`.  
  Example:  
  ```
  Input: H2 + O2 -> H2O  
  Output: (2) H2 + (1) O2 -> (2) H2O
  ```

- **Water of Crystallization:**  
  
  The program can handle chemical equations involving water of crystallization, represented as `.H2O` in the reactants or products.  
  Example:  
  ```
  Input: CuSO4.5H2O -> CuSO4 + H2O  
  Output: (1) CuSO4.5H2O -> (1) CuSO4 + (5) H2O
  ```

- **Ionic Equations:**  
  
  The program supports balancing equations that involve ions, where ions are denoted inside `{ }`.  
  Example:  
  ```
  Input: Fe{+3} + I{-1} -> Fe{+2} + I2  
  Output: (2) Fe{+3} + (2) I{-1} -> (2) Fe{+2} + (1) I2
  ```

- **Electron (e⁻) Support:**  
  
  Equations involving electrons can also be balanced.  
  Example:  
  ```
  Input: O2 + H{+1} + e -> H2O  
  Output: (1) O2 + (4) H{+1} + (4) e -> (2) H2O
  ```

## Input Format for Program

![Screenshot 2024-09-17 055203](https://github.com/user-attachments/assets/4fee5daa-39f5-4d61-8666-a1c2369d329a)

- **Equation Format:**

    Reactants and Products are separated with separator `->`

    Chemical Species on either side must be separated with space and + sign

    Input Example: `H2 + O2 -> H2O`
- **Casing:**

    Follows the conventional casing for writing chemical equations.
        
    - Element must start with capital letter. `H`
    - For elements with multiple letter, first letter is capital and other are small. `Fe`
- **Compounds :** 

    Being terminal based it does not support superscritps and subscripts, thus reaction must be written in simpler way.
    
    H<sub>2</sub>O as H2O
- **Paranthesis:**

    Compounds involving paranthesis are written as follows

    Ca(OH)<sub>2</sub> as Ca(OH)2

- **Ions** 

    - Charges for a chemical species is written inside curly braces {} after chemical species with no space

    Fe<sup>+3</sup> as Fe{+3} or Fe{3}

    - Electron is simply written as `e`

### Example Inputs
```
1. H2 + O2 -> H2O
2. CuSO4.5H2O -> CuSO4 + H2O
3. Fe{+3} + I{-1} -> Fe{+2} + I2
4. O2 + H{+1} + e -> H2O
```

## Compilation and Usage

1. **Compilation:**
   
   Linux
   ```bash
   g++ main.cpp -o balancer
   ```
   Windows
   ```bash
   g++ main.cpp -o balancer.exe
   ```

2. **Running the Program:**
   
   Linux
   ```bash
   ./balancer
   ```
   Windows
    ```bash
   ./balancer.exe
   ```


## Room For Improvements

- Additional error handling for invalid input formats.
- Better Code Restructuring and following best practices
- Error Case Checking
- Support for Nuclear Reactions
- It is purely mathematical and does not take consideration for whether specified element exist or not.
