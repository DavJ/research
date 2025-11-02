#!/usr/bin/env python3
"""
UBT Integration Helper Tool

This script helps with integrating research repository content into the
Unified Biquaternion Theory (UBT) repository.

Features:
- Scan and catalog LaTeX files
- Extract equations from LaTeX files
- Validate file structure
- Generate integration reports
- Check cross-references

Author: GitHub Copilot Agent
Date: November 2, 2025
"""

import os
import re
import json
from pathlib import Path
from typing import Dict, List, Tuple
import argparse


class UBTIntegrationHelper:
    """Helper class for UBT integration tasks."""
    
    def __init__(self, repo_root: str):
        """Initialize with repository root directory."""
        self.repo_root = Path(repo_root)
        self.latex_files = []
        self.equations = {}
        self.file_metadata = {}
        
    def scan_latex_files(self) -> List[Path]:
        """Scan repository for LaTeX files."""
        print("Scanning for LaTeX files...")
        latex_files = list(self.repo_root.rglob("*.tex"))
        self.latex_files = [f for f in latex_files if '.git' not in str(f)]
        print(f"Found {len(self.latex_files)} LaTeX files")
        return self.latex_files
    
    def extract_equations(self, file_path: Path) -> List[str]:
        """Extract equations from a LaTeX file."""
        try:
            with open(file_path, 'r', encoding='utf-8') as f:
                content = f.read()
            
            # Extract display equations
            display_equations = re.findall(r'\$\$(.*?)\$\$', content, re.DOTALL)
            
            # Extract inline equations
            inline_equations = re.findall(r'\$(.*?)\$', content)
            
            # Extract equation environments
            env_equations = re.findall(
                r'\\begin\{equation\}(.*?)\\end\{equation\}', 
                content, 
                re.DOTALL
            )
            
            all_equations = display_equations + inline_equations + env_equations
            return [eq.strip() for eq in all_equations if eq.strip()]
            
        except Exception as e:
            print(f"Error reading {file_path}: {e}")
            return []
    
    def analyze_file(self, file_path: Path) -> Dict:
        """Analyze a single LaTeX file."""
        rel_path = file_path.relative_to(self.repo_root)
        equations = self.extract_equations(file_path)
        
        # Get file size
        file_size = file_path.stat().st_size
        
        # Count lines
        try:
            with open(file_path, 'r', encoding='utf-8') as f:
                line_count = len(f.readlines())
        except:
            line_count = 0
        
        metadata = {
            'path': str(rel_path),
            'full_path': str(file_path),
            'size_bytes': file_size,
            'line_count': line_count,
            'equation_count': len(equations),
            'equations': equations[:10],  # First 10 equations only
            'category': self.categorize_file(rel_path)
        }
        
        return metadata
    
    def categorize_file(self, rel_path: Path) -> str:
        """Categorize file by directory."""
        parts = rel_path.parts
        if 'theory-of-everything' in parts:
            return 'Core Biquaternion Theory'
        elif 'hyperspace-waves-simple' in parts:
            return 'Hyperspace Waves'
        elif 'FTL-problem' in parts:
            return 'FTL Transformations'
        elif 'green-book' in parts:
            return 'Green Book Calculations'
        elif 'wave-packet' in parts:
            return 'Wave Packet Analysis'
        else:
            return 'Other'
    
    def generate_catalog(self) -> Dict:
        """Generate complete catalog of LaTeX files."""
        print("\nGenerating catalog...")
        catalog = {
            'total_files': len(self.latex_files),
            'categories': {},
            'files': []
        }
        
        for file_path in self.latex_files:
            metadata = self.analyze_file(file_path)
            catalog['files'].append(metadata)
            
            # Group by category
            category = metadata['category']
            if category not in catalog['categories']:
                catalog['categories'][category] = []
            catalog['categories'][category].append(metadata)
        
        return catalog
    
    def print_summary(self, catalog: Dict):
        """Print summary of catalog."""
        print("\n" + "="*60)
        print("UBT INTEGRATION CATALOG SUMMARY")
        print("="*60)
        print(f"\nTotal LaTeX files: {catalog['total_files']}")
        print(f"\nFiles by category:")
        
        for category, files in sorted(catalog['categories'].items()):
            print(f"\n  {category}: {len(files)} files")
            total_equations = sum(f['equation_count'] for f in files)
            print(f"    Total equations: {total_equations}")
            
            # List files in category
            for f in files[:5]:  # Show first 5
                print(f"    - {f['path']} ({f['equation_count']} equations)")
            if len(files) > 5:
                print(f"    ... and {len(files) - 5} more files")
    
    def save_catalog(self, catalog: Dict, output_file: str):
        """Save catalog to JSON file."""
        output_path = self.repo_root / output_file
        print(f"\nSaving catalog to {output_path}...")
        
        with open(output_path, 'w', encoding='utf-8') as f:
            json.dump(catalog, f, indent=2, ensure_ascii=False)
        
        print(f"Catalog saved successfully!")
    
    def validate_references(self) -> List[Tuple[Path, str]]:
        """Validate cross-references between files."""
        print("\nValidating cross-references...")
        issues = []
        
        # This is a simplified validation
        # In a real scenario, we'd parse \ref{}, \cite{}, etc.
        
        for file_path in self.latex_files:
            try:
                with open(file_path, 'r', encoding='utf-8') as f:
                    content = f.read()
                
                # Look for \ref{} commands
                refs = re.findall(r'\\ref\{([^}]+)\}', content)
                
                # Look for \label{} commands
                labels = re.findall(r'\\label\{([^}]+)\}', content)
                
                if refs and not labels:
                    rel_path = file_path.relative_to(self.repo_root)
                    issues.append((rel_path, f"Has {len(refs)} references but no labels"))
                    
            except Exception as e:
                pass
        
        return issues
    
    def check_integration_readiness(self) -> Dict[str, bool]:
        """Check if content is ready for integration."""
        print("\nChecking integration readiness...")
        
        checks = {
            'has_core_definitions': False,
            'has_energy_formulas': False,
            'has_hyperspace_waves': False,
            'has_ftl_transforms': False,
            'manifest_exists': False,
            'guide_exists': False
        }
        
        # Check for key files
        for file_path in self.latex_files:
            rel_path = str(file_path.relative_to(self.repo_root))
            
            if 'biquaternion-gradient' in rel_path:
                checks['has_core_definitions'] = True
            if 'energy' in rel_path:
                checks['has_energy_formulas'] = True
            if 'hyperspace-waves-simple' in rel_path:
                checks['has_hyperspace_waves'] = True
        
        # Check for FTL problem files
        ftl_dir = self.repo_root / 'FTL-problem'
        if ftl_dir.exists():
            checks['has_ftl_transforms'] = True
        
        # Check for documentation
        manifest = self.repo_root / 'UBT_INTEGRATION_MANIFEST.md'
        checks['manifest_exists'] = manifest.exists()
        
        guide = self.repo_root / 'UBT_INTEGRATION_GUIDE.md'
        checks['guide_exists'] = guide.exists()
        
        return checks
    
    def print_readiness_report(self, checks: Dict[str, bool]):
        """Print integration readiness report."""
        print("\n" + "="*60)
        print("INTEGRATION READINESS REPORT")
        print("="*60)
        
        all_ready = all(checks.values())
        
        for check, status in checks.items():
            icon = "✅" if status else "❌"
            readable_name = check.replace('_', ' ').title()
            print(f"{icon} {readable_name}")
        
        print("\n" + "="*60)
        if all_ready:
            print("✅ READY FOR INTEGRATION")
        else:
            print("⚠️  SOME ITEMS NEED ATTENTION")
        print("="*60)


def main():
    """Main function."""
    parser = argparse.ArgumentParser(
        description='UBT Integration Helper Tool'
    )
    parser.add_argument(
        '--repo-root',
        default='.',
        help='Root directory of repository (default: current directory)'
    )
    parser.add_argument(
        '--output',
        default='ubt_integration_catalog.json',
        help='Output file for catalog (default: ubt_integration_catalog.json)'
    )
    parser.add_argument(
        '--skip-save',
        action='store_true',
        help='Skip saving catalog to file'
    )
    
    args = parser.parse_args()
    
    print("="*60)
    print("UBT Integration Helper Tool")
    print("="*60)
    
    # Initialize helper
    helper = UBTIntegrationHelper(args.repo_root)
    
    # Scan for LaTeX files
    helper.scan_latex_files()
    
    # Generate catalog
    catalog = helper.generate_catalog()
    
    # Print summary
    helper.print_summary(catalog)
    
    # Save catalog
    if not args.skip_save:
        helper.save_catalog(catalog, args.output)
    
    # Check readiness
    checks = helper.check_integration_readiness()
    helper.print_readiness_report(checks)
    
    # Validate references
    issues = helper.validate_references()
    if issues:
        print(f"\n⚠️  Found {len(issues)} potential cross-reference issues")
        for path, issue in issues[:5]:
            print(f"  - {path}: {issue}")
        if len(issues) > 5:
            print(f"  ... and {len(issues) - 5} more")
    else:
        print("\n✅ No cross-reference issues found")
    
    print("\n" + "="*60)
    print("Integration helper completed successfully!")
    print("="*60)


if __name__ == '__main__':
    main()
