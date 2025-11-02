#!/usr/bin/env python3
"""
Example: Extracting and Working with UBT Content

This example demonstrates how to programmatically work with the
integration catalog and extract content for UBT integration.

Author: GitHub Copilot Agent
Date: November 2, 2025
"""

import json
from pathlib import Path
from typing import List, Dict


def load_catalog(catalog_path: str = 'ubt_integration_catalog.json') -> Dict:
    """Load the integration catalog."""
    with open(catalog_path, 'r') as f:
        return json.load(f)


def get_files_by_category(catalog: Dict, category: str) -> List[Dict]:
    """Get all files in a specific category."""
    return catalog['categories'].get(category, [])


def print_category_summary(catalog: Dict):
    """Print a summary of all categories."""
    print("="*70)
    print("CATEGORY SUMMARY")
    print("="*70)
    
    for category, files in sorted(catalog['categories'].items()):
        print(f"\n{category}:")
        print(f"  Files: {len(files)}")
        print(f"  Total lines: {sum(f['line_count'] for f in files)}")
        print(f"  Total equations: {sum(f['equation_count'] for f in files)}")


def extract_core_definitions(catalog: Dict) -> List[str]:
    """Extract paths of core biquaternion definition files."""
    core_files = get_files_by_category(catalog, 'Core Biquaternion Theory')
    
    # Filter for key definition files
    definitions = []
    keywords = ['gradient', 'vector-potential', 'eight-intensity', 'scalar-component']
    
    for file_info in core_files:
        path = file_info['path']
        if any(keyword in path for keyword in keywords):
            definitions.append(file_info)
    
    return definitions


def create_integration_plan(catalog: Dict) -> Dict[str, List[str]]:
    """Create a phased integration plan."""
    plan = {
        'Phase 1 - Core Definitions': [],
        'Phase 2 - Energy Formulations': [],
        'Phase 3 - Hyperspace Waves': [],
        'Phase 4 - Other': []
    }
    
    # Core definitions
    core_files = get_files_by_category(catalog, 'Core Biquaternion Theory')
    keywords_core = ['gradient', 'vector-potential', 'eight-intensity', 'scalar-component']
    for f in core_files:
        if any(kw in f['path'] for kw in keywords_core):
            plan['Phase 1 - Core Definitions'].append(f['path'])
    
    # Energy formulations
    keywords_energy = ['energy']
    for f in core_files:
        if any(kw in f['path'] for kw in keywords_energy):
            plan['Phase 2 - Energy Formulations'].append(f['path'])
    
    # Hyperspace waves
    hw_files = get_files_by_category(catalog, 'Hyperspace Waves')
    plan['Phase 3 - Hyperspace Waves'] = [f['path'] for f in hw_files]
    
    # Other
    for category, files in catalog['categories'].items():
        if category not in ['Core Biquaternion Theory', 'Hyperspace Waves']:
            plan['Phase 4 - Other'].extend([f['path'] for f in files])
    
    return plan


def print_integration_plan(plan: Dict[str, List[str]]):
    """Print the integration plan."""
    print("\n" + "="*70)
    print("INTEGRATION PLAN")
    print("="*70)
    
    for phase, files in plan.items():
        print(f"\n{phase}:")
        print(f"  Total files: {len(files)}")
        for i, file_path in enumerate(files[:5], 1):  # Show first 5
            print(f"    {i}. {file_path}")
        if len(files) > 5:
            print(f"    ... and {len(files) - 5} more files")


def generate_file_mapping(catalog: Dict) -> List[Dict[str, str]]:
    """Generate suggested file mappings for UBT integration."""
    mappings = []
    
    # Core definitions mapping
    core_files = get_files_by_category(catalog, 'Core Biquaternion Theory')
    
    mapping_rules = {
        'biquaternion-gradient': 'definitions/operators.tex',
        'biquaternion-vector-potential': 'definitions/potentials.tex',
        'biquaternion-eight-intensity-meaning': 'theory/field-strength.tex',
        'biquaternion-eight-intensity.tex': 'theory/field-strength.tex',
        'scalar-component': 'definitions/scalar-field.tex',
        'energy-real-G': 'theory/energy-density.tex',
        'energy-complex-G': 'theory/energy-density-advanced.tex',
    }
    
    for file_info in core_files:
        source = file_info['path']
        for keyword, target in mapping_rules.items():
            if keyword in source:
                mappings.append({
                    'source': source,
                    'target': target,
                    'category': 'Core Theory'
                })
                break
    
    # Hyperspace waves mapping
    hw_files = get_files_by_category(catalog, 'Hyperspace Waves')
    for file_info in hw_files:
        mappings.append({
            'source': file_info['path'],
            'target': 'extensions/hyperspace-waves/',
            'category': 'Hyperspace Waves'
        })
    
    return mappings


def print_file_mappings(mappings: List[Dict[str, str]]):
    """Print file mappings in a readable format."""
    print("\n" + "="*70)
    print("SUGGESTED FILE MAPPINGS")
    print("="*70)
    
    # Group by category
    by_category = {}
    for mapping in mappings:
        cat = mapping['category']
        if cat not in by_category:
            by_category[cat] = []
        by_category[cat].append(mapping)
    
    for category, maps in by_category.items():
        print(f"\n{category}:")
        for m in maps[:10]:  # Show first 10 per category
            source = m['source'].split('/')[-1]  # Just filename
            target = m['target'].split('/')[-1]  # Just filename
            print(f"  {source:45} → {target}")
        if len(maps) > 10:
            print(f"  ... and {len(maps) - 10} more mappings")


def read_latex_file(file_path: str) -> str:
    """Read content of a LaTeX file."""
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            return f.read()
    except Exception as e:
        return f"Error reading file: {e}"


def show_sample_content(catalog: Dict, num_samples: int = 3):
    """Show sample content from LaTeX files."""
    print("\n" + "="*70)
    print("SAMPLE CONTENT FROM LATEX FILES")
    print("="*70)
    
    core_files = get_files_by_category(catalog, 'Core Biquaternion Theory')
    
    # Show first few files
    for i, file_info in enumerate(core_files[:num_samples], 1):
        print(f"\n{i}. {file_info['path']}")
        print(f"   Size: {file_info['size_bytes']} bytes, Lines: {file_info['line_count']}")
        print(f"   Content preview:")
        
        content = read_latex_file(file_info['full_path'])
        lines = content.split('\n')[:5]  # First 5 lines
        for line in lines:
            print(f"   | {line}")
        if len(content.split('\n')) > 5:
            print(f"   | ... ({len(content.split('\n')) - 5} more lines)")


def generate_markdown_table(mappings: List[Dict[str, str]], limit: int = 20) -> str:
    """Generate a markdown table of file mappings."""
    table = "| Source File | Target File | Category |\n"
    table += "|------------|-------------|----------|\n"
    
    for mapping in mappings[:limit]:
        source = mapping['source'].split('/')[-1]
        target = mapping['target']
        category = mapping['category']
        table += f"| {source} | {target} | {category} |\n"
    
    if len(mappings) > limit:
        table += f"\n*... and {len(mappings) - limit} more mappings*\n"
    
    return table


def main():
    """Main function demonstrating integration workflow."""
    print("="*70)
    print("UBT INTEGRATION EXAMPLE")
    print("="*70)
    
    # Load catalog
    print("\nLoading integration catalog...")
    catalog = load_catalog()
    print(f"✅ Loaded catalog with {catalog['total_files']} files")
    
    # Show category summary
    print_category_summary(catalog)
    
    # Extract core definitions
    print("\n" + "="*70)
    print("CORE DEFINITIONS")
    print("="*70)
    core_defs = extract_core_definitions(catalog)
    print(f"\nFound {len(core_defs)} core definition files:")
    for i, def_file in enumerate(core_defs, 1):
        print(f"  {i}. {def_file['path']}")
    
    # Create integration plan
    plan = create_integration_plan(catalog)
    print_integration_plan(plan)
    
    # Generate file mappings
    mappings = generate_file_mapping(catalog)
    print_file_mappings(mappings)
    
    # Show sample content
    show_sample_content(catalog)
    
    # Generate markdown table
    print("\n" + "="*70)
    print("MARKDOWN TABLE FOR DOCUMENTATION")
    print("="*70)
    table = generate_markdown_table(mappings)
    print("\n" + table)
    
    # Summary
    print("\n" + "="*70)
    print("SUMMARY")
    print("="*70)
    print(f"Total files analyzed: {catalog['total_files']}")
    print(f"Categories: {len(catalog['categories'])}")
    print(f"Core definitions: {len(core_defs)}")
    print(f"File mappings generated: {len(mappings)}")
    print("\n✅ Integration example completed successfully!")
    print("="*70)


if __name__ == '__main__':
    main()
